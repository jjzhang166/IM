//
//  LocalStorageUserData.cpp
//  BabyGenius
//
//  Created by Chydison on 14/11/8.
//
//

#include "LocalStorageUserData.h"
#include "CrossApp.h"
#if (CC_TARGET_PLATFORM != CC_PLATFORM_ANDROID && CC_TARGET_PLATFORM != CC_PLATFORM_TIZEN)
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <sqlite3.h>

static int _initialized_userData = 0;
static sqlite3 *_db_userData;
static sqlite3_stmt *_stmt_select_userData;
static sqlite3_stmt *_stmt_remove_userData;
static sqlite3_stmt *_stmt_update_userData;


//static void localStorageUserDataLazyInit();
static void localStorageUserDataCreateTable();

static void localStorageUserDataCreateTable()
{
    const char *sql_createtable = "CREATE TABLE IF NOT EXISTS data(key TEXT PRIMARY KEY,value TEXT);";
    sqlite3_stmt *stmt;
    int ok=sqlite3_prepare_v2(_db_userData, sql_createtable, -1, &stmt, NULL);
    ok |= sqlite3_step(stmt);
    ok |= sqlite3_finalize(stmt);
    
    if( ok != SQLITE_OK && ok != SQLITE_DONE)
        printf("Error in CREATE TABLE\n");
}

void localStorageUserDataInit( const char *fullpath)
{
    if( ! _initialized_userData )
    {
        
        int ret = 0;
        
        if (!fullpath)
            ret = sqlite3_open(":memory:",&_db_userData);
        else
            ret = sqlite3_open(fullpath, &_db_userData);
        
        localStorageUserDataCreateTable();
        
        // SELECT
        const char *sql_select = "SELECT value FROM data WHERE key=?;";
        ret |= sqlite3_prepare_v2(_db_userData, sql_select, -1, &_stmt_select_userData, NULL);
        
        // REPLACE
        const char *sql_update = "REPLACE INTO data (key, value) VALUES (?,?);";
        ret |= sqlite3_prepare_v2(_db_userData, sql_update, -1, &_stmt_update_userData, NULL);
        
        // DELETE
        const char *sql_remove = "DELETE FROM data WHERE key=?;";
        ret |= sqlite3_prepare_v2(_db_userData, sql_remove, -1, &_stmt_remove_userData, NULL);
        
        if( ret != SQLITE_OK ) {
            printf("Error initializing DB\n");
            // report error
        }
        
        _initialized_userData = 1;
    }
}

void localStorageUserDataFree()
{
    if( _initialized_userData ) {
        sqlite3_finalize(_stmt_select_userData);
        sqlite3_finalize(_stmt_remove_userData);
        sqlite3_finalize(_stmt_update_userData);
        
        sqlite3_close(_db_userData);
        
        _initialized_userData = 0;
    }
}

/** sets an item in the LS */
void localStorageUserDataSetItem( const char *key, const char *value)
{
    assert( _initialized_userData );
    
    int ok = sqlite3_bind_text(_stmt_update_userData, 1, key, -1, SQLITE_TRANSIENT);
    ok |= sqlite3_bind_text(_stmt_update_userData, 2, value, -1, SQLITE_TRANSIENT);
    
    ok |= sqlite3_step(_stmt_update_userData);
    
    ok |= sqlite3_reset(_stmt_update_userData);
    
    if( ok != SQLITE_OK && ok != SQLITE_DONE)
        printf("Error in localStorageUserData.setItem()\n");
}

/** gets an item from the LS */
const char* localStorageUserDataGetItem( const char *key )
{
    assert( _initialized_userData );
    int ok = sqlite3_reset(_stmt_select_userData);
    
    ok |= sqlite3_bind_text(_stmt_select_userData, 1, key, -1, SQLITE_TRANSIENT);
    ok |= sqlite3_step(_stmt_select_userData);
    const unsigned char *ret = sqlite3_column_text(_stmt_select_userData, 0);
    
    //CCLog("sqlite key-value: %s---%s",key,ret);
    
    if( ok != SQLITE_OK && ok != SQLITE_DONE && ok != SQLITE_ROW)
        printf("Error in localStorageUserData.getItem()\n");
    
    return (const char*)ret;
}

/** removes an item from the LS */
void localStorageUserDataRemoveItem( const char *key )
{
    assert( _initialized_userData );
    
    int ok = sqlite3_bind_text(_stmt_remove_userData, 1, key, -1, SQLITE_TRANSIENT);
    
    ok |= sqlite3_step(_stmt_remove_userData);
    
    ok |= sqlite3_reset(_stmt_remove_userData);
    
    if( ok != SQLITE_OK && ok != SQLITE_DONE)
        printf("Error in localStorageUserData.removeItem()\n");
}

#endif
