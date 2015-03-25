#include "IMUserManager.h"
#include "RootWindow.h"
User::User()
{

}
User::~User()
{

}
bool User::init(std::string p_uid, std::string p_nickname, std::string p_sex, std::string p_photo, std::string p_signature, UserStatus p_status)
{
	uid = p_uid;
	nickname = p_nickname;
	sex = p_sex;
	photo = p_photo;
	signature = p_signature;
	status = p_status;
	return true;
}

#pragma IMUserManager
static IMUserManager* p_UserManager = NULL;

IMUserManager* IMUserManager::Instance()
{
	if (p_UserManager == NULL)
	{
		p_UserManager = new IMUserManager();
	}
	return p_UserManager;
}

void IMUserManager::destroyInstance()
{
	if (p_UserManager)
	{
		delete p_UserManager;
		p_UserManager = NULL;
	}
}

IMUserManager::IMUserManager()
{
	int ret = 0;
	const char* sql_createtable = "CREATE TABLE IF NOT EXISTS user(id int auto_increment, uid VARCHAR(50), nickname VARCHAR(256),sex VARCHAR(50), photo VARCHAR(256),signature VARCHAR(512), status int);";
	sqlite3_stmt *stmt;
	int ok = sqlite3_prepare_v2(RootWindow::getInstance()->getSqlite3(), sql_createtable, -1, &stmt, NULL);
	ok |= sqlite3_step(stmt);
	ok |= sqlite3_finalize(stmt);
	if (ok != SQLITE_OK && ok != SQLITE_DONE)
	{
		CCLog("open table wrong");
	}

	const char *sql_delete = "DELETE FROM user WHERE uid = ? ;";
	ret |= sqlite3_prepare_v2(RootWindow::getInstance()->getSqlite3(), sql_delete, -1, &_sqlite_stmt_delete, NULL);

	const char *sql_stmt_login = "INSERT INTO user (uid, nickname, sex, photo, signature,status) VALUES (?,?,?,?,?,?);";
	ret |= sqlite3_prepare_v2(RootWindow::getInstance()->getSqlite3(), sql_stmt_login, -1, &_sqlite_stmt_login, NULL);

	const char *sql_stmt_logout = "UPDATE user SET status = 0 WHERE uid = (SELECT uid FROM user WHERE status = 1 LIMIT 1);";
	ret |= sqlite3_prepare_v2(RootWindow::getInstance()->getSqlite3(), sql_stmt_logout, -1, &_sqlite_stmt_logout, NULL);

	const char* sql_stmt_select_online = " SELECT uid, nickname, sex, photo, signature, status FROM user WHERE status = 1 LIMIT 1; ";
	ret |= sqlite3_prepare_v2(RootWindow::getInstance()->getSqlite3(), sql_stmt_select_online, -1, &_sqlite_stmt_online, NULL);
}

IMUserManager::~IMUserManager()
{
	sqlite3_finalize(_sqlite_stmt_delete);
	sqlite3_finalize(_sqlite_stmt_login);
	sqlite3_finalize(_sqlite_stmt_logout);
	sqlite3_finalize(_sqlite_stmt_online);
}

bool IMUserManager::userLogin(User user)
{
	_delete(user.uid);
	char val[10];
	sprintf(val, "%d", user.status);
	const char* status_sqlite = val;
	int ok = sqlite3_bind_text(_sqlite_stmt_login,1,user.uid.c_str(),-1,SQLITE_TRANSIENT);
	ok |= sqlite3_bind_text(_sqlite_stmt_login, 2, user.nickname.c_str(), -1, SQLITE_TRANSIENT);
	ok |= sqlite3_bind_text(_sqlite_stmt_login, 3, user.sex.c_str(), -1, SQLITE_TRANSIENT);
	ok |= sqlite3_bind_text(_sqlite_stmt_login, 4, user.photo.c_str(), -1, SQLITE_TRANSIENT);
	ok |= sqlite3_bind_text(_sqlite_stmt_login, 5, user.signature.c_str(), -1, SQLITE_TRANSIENT);
	ok |= sqlite3_bind_text(_sqlite_stmt_login, 6, status_sqlite, -1, SQLITE_TRANSIENT);
	ok |= sqlite3_step(_sqlite_stmt_login);
	ok |= sqlite3_reset(_sqlite_stmt_login);
	if (ok != SQLITE_OK && ok != SQLITE_DONE)
	{
		CCLog("LOGIN wrong");
		return false;
	}
	return true;
}

bool IMUserManager::userLogout()
{
	int ok = sqlite3_step(_sqlite_stmt_logout);
	ok |= sqlite3_reset(_sqlite_stmt_logout);
	if (ok != SQLITE_OK && ok != SQLITE_DONE){
		printf("LogOut wrong");
		return false;
	}
	return true;
}

User* IMUserManager::onLineUser()
{
	int ok = SQLITE_OK;
	User *user = new User();
	if (sqlite3_step(_sqlite_stmt_online) == SQLITE_ROW){
		const unsigned char *m_uid = sqlite3_column_text(_sqlite_stmt_online, 0);
		const unsigned char *m_nickname = sqlite3_column_text(_sqlite_stmt_online, 1);
		const unsigned char *m_sex = sqlite3_column_text(_sqlite_stmt_online, 2);
		const unsigned char *m_photo = sqlite3_column_text(_sqlite_stmt_online, 3);
		const unsigned char *m_signature = sqlite3_column_text(_sqlite_stmt_online, 4);
		const int m_status = sqlite3_column_int(_sqlite_stmt_online, 5);
		user->init((const char*)m_uid, (const char*)m_nickname, (const char*)m_sex, (const char*)m_photo, (const char*)m_signature, (UserStatus)m_status);
	}
	ok |= sqlite3_reset(_sqlite_stmt_online);
	if (ok != SQLITE_OK && ok != SQLITE_DONE)
	{
		CCLog("select user wrong");
	}
	return user;
}

void IMUserManager::_delete(std::string uid)
{
	int ok = sqlite3_bind_text(_sqlite_stmt_delete, 1, uid.c_str(), -1, SQLITE_TRANSIENT);
	ok |= sqlite3_step(_sqlite_stmt_delete);
	ok |= sqlite3_reset(_sqlite_stmt_delete);
	if (ok != SQLITE_OK && ok != SQLITE_DONE)
		printf("delete user wrong");
}