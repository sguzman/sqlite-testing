#include <iostream>
#include <sqlite3.h>
#include "crow_all.h"

using std::cout;
using std::endl;
using std::cerr;

[[noreturn]] static inline void panic(const char* const errMsg) noexcept {
  cout << errMsg << endl;
  exit(EXIT_FAILURE);
}

static inline int callback(void *, int argc, char** argv, char** azColName) noexcept {
  for(auto i = 0u; i < argc; i++)
  {
    cout << azColName[i] <<" = " << (argv[i] ? argv[i] : "NULL") << endl;
  }
  cout << endl;
  return 0;
}

static inline const char * const resp(const std::string& str) noexcept {
  return str.c_str();
}

int main() noexcept {
  sqlite3* db;
  int rc{sqlite3_open("../item.db", &db)};
  {
    if(rc) {
      panic(sqlite3_errmsg(db));
    } else {
      cout << "Open database successfully" << endl;
    }
  }

  {
    crow::SimpleApp app{};

    CROW_ROUTE(app, "/<string>")(resp);

    app
        .port(8080)
        .bindaddr("0.0.0.0")
        .concurrency(8)
        .multithreaded()
        .run();
  }

  {
    rc = sqlite3_exec(db, "SELECT * FROM ebooks", callback, nullptr, nullptr);
    if (rc != SQLITE_OK) {
      panic(sqlite3_errmsg(db));
    }
  }

  {
    sqlite3_close(db);
    return EXIT_SUCCESS;
  }
}