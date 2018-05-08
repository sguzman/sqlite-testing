#include <iostream>
#include <sqlite3.h>

using std::cout;
using std::endl;
using std::cerr;

static inline int callback(void *, int argc, char **argv, char **azColName) noexcept {
  for(auto i = 0u; i< argc; i++)
  {
    cout << azColName[i] <<" = " << (argv[i] ? argv[i] : "NULL") << endl;
  }
  cout << endl;
  return 0;
}

int main() noexcept {
  sqlite3* db;
  int rc{sqlite3_open("../item.db", &db)};
  {
    if(rc) {
      cerr << "Can't open database: " << sqlite3_errmsg(db) << endl;
      return EXIT_FAILURE;
    } else {
      cout << "Open database successfully" << endl;
    }
  }

  {
    rc = sqlite3_exec(db, "SELECT * FROM ebooks", callback, nullptr, nullptr);
    if (rc != SQLITE_OK) {
      cerr << "Something bad happened: " << sqlite3_errmsg(db) << endl;
    }
  }

  {

  }
}