#ifndef DATABASEGNUCASH
#define DATABASEGNUCASH

  // Standard C++ library definitions.

#include <cstdint>
#include <memory>
#include <vector>

#include "include/qt.h"

#include "include/database.h"

#include <GCL>

struct SCommodityValue
{
  std::uint16_t year;       // Full year value (2018)
  std::uint16_t month;      // Month 1- January
  std::uint16_t day;        // Day 1 - 1st day of month.
  std::string source;
  std::string type;
  double value;
};

typedef std::vector<SCommodityValue> DCommodityValues;

class CGnuCashDatabase : public QCL::CDatabase
{
private:
  GCL::sqlwriter::CSQLWriter sqlWriter;
  std::unique_ptr<QSqlQuery> sqlQuery;       ///< Pointer to the query that will be used

  void processErrorInformation() const;

protected:
public:
  CGnuCashDatabase();

  bool createConnection(QString const &, QString const &, std::uint16_t, QString const &, QString const &, QString const &);

  bool writeCurrencyValues(DCommodityValues const &, std::string const &commodityName, std::string const &currencyName);
};

#endif // DATABASEGNUCASH

