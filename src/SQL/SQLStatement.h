//
// Created by David van Laatum on 26/3/17.
//

#ifndef DBTABLEUSAGECPP_SQLSTATEMENT_H
#define DBTABLEUSAGECPP_SQLSTATEMENT_H

#include <map>
#include "SQLObject.h"
#include "SQLTable.h"

class SQLStatement : public SQLObject {
public:
    enum TableFlags {
        READ = 1,
        WRITE = 2,
        INSERT = 4,
        UPDATE = 8,
        DELETE = 16,
        ALTER = 32
    };
    typedef std::map<boost::shared_ptr<SQLTable>, int> table_type;
    virtual ~SQLStatement ();
    virtual void getTables ( table_type &rt ) const = 0;
};


#endif //DBTABLEUSAGECPP_SQLSTATEMENT_H
