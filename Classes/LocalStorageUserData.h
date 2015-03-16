//
//  LocalStorageUserData.h
//  BabyGenius
//
//  Created by Chydison on 14/11/8.
//
//

#ifndef __BabyGenius__LocalStorageUserData__
#define __BabyGenius__LocalStorageUserData__

#include <stdio.h>
#include <stdlib.h>

/** Initializes the database. If path is null, it will create an in-memory DB */
void localStorageUserDataInit( const char *fullpath);

/** Frees the allocated resources */
void localStorageUserDataFree();

/** sets an item in the LS */
void localStorageUserDataSetItem( const char *key, const char *value);

/** gets an item from the LS */
const char* localStorageUserDataGetItem( const char *key );

/** removes an item from the LS */
void localStorageUserDataRemoveItem( const char *key );

#endif /* defined(__BabyGenius__LocalStorageUserData__) */
