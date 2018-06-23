#include "../include/databaseGnuCash.h"

  // Standard C++ library header files.

#include <cmath>
#include <limits>

/// @brief Constructor for the database class.
/// @throws None.
/// @version 2018-06-23/GGB - Function created.

CGnuCashDatabase::CGnuCashDatabase() : CDatabase("GNUCASH"), sqlQuery()
{

}

bool CGnuCashDatabase::createConnection(QString const &driverName, QString const &hostName, std::uint16_t portNumber,
                                 QString const &databaseName,
                                 QString const &userName, QString const &password)
{
  bool returnValue;

  returnValue = CDatabase::createConnection(driverName, hostName, portNumber, databaseName, userName, password);

  if (returnValue)
  {
    sqlQuery.reset(new QSQLQuery(*dBase));
  };

  return returnValue;

}

/// @brief Processes and displays the error information.
/// @throws None.
/// @version 2017-08-13/GGB - FUnction created.

void CGnuCashDatabase::processErrorInformation() const
{
  QSqlError error = sqlQuery->lastError();

  ERRORMESSAGE("Error while executing query: " + sqlWriter.string());
  ERRORMESSAGE("Error returned by Driver: " + error.nativeErrorCode().toStdString());
  ERRORMESSAGE("Text returned by driver: " + error.driverText().toStdString());
  ERRORMESSAGE("Text returned by database: " + error.databaseText().toStdString());
};

/// @brief Writes currency records to the database.
/// @param[in] commodityValues: The commodity values to write.
/// @param[in] commodityName: The name of the commodity to write.
/// @param[in] currencyName: The name of the currency to use.
/// @returns
/// @throws
/// @version 2018-06-23/GGB - Function created.

bool CGnuCashDatabase::writeCurrencyValues(DCommodityValues const &commodityValues, std::string const &commodityName,
                                           std::string const &currencyName)
{
  std::string commodityGUID;
  std::string currencyGUID;


    // Database structure
    //  GUID
    //  commodity_guid
    //  currency_guid
    //  date -> 2020-06-07 16:00:00
    //  source -> user:price      user:price_editor   user:split_register   Finance::Quote
    //  type -> transaction     last
    //  value_num
    //  value_denom

  sqlWriter.resetQuery();
  sqlWriter.insertInto("prices",
  {"guid", "commodity_guid", "currency_guid", "date", "source", "type", "value_num", "value_denom"})
      .values(GCL::sqlwriter::bindValue(":guid"), commodityGUID, currencyGUID, GCL::sqlwriter::bindValue(":date"),
             "Finance::Quote", "last", GCL::sqlwriter::bindValue(":numerator"), GCL::sqlwriter::bindValue("denominator"));

  sqlQuery->clear();
  sqlQuery->prepare(QString::fromStdString(sqlWriter.string()));

  for (auto cv : commodityValues)
  {
    std::uint64_t numerator;
    std::uint64_t denominator;
    std::string GUID;

    if (std::floor(cv.value) < static_cast<double>(std::numeric_limits<std::uint64_t>::max()) )
    {
      double temp;
      std::uint_least8_t digitCounter = 0;

      numerator = std::floor(cv.value);
      cv.value -= std::floor(cv.value);
      denominator = 1;

      while(std::modf(cv.value * denominator, &temp) && (digitCounter <= 10) )
      {
        denominator *= 10;
        digitCounter++;
      };

      denominator = std::floor(cv.value * denominator);
    }
    else
    {

    }

    sqlQuery->bindValue(":guid", QUuid::createUuid().toString());
    sqlQuery->bindValue(":date", boost::str(boost::format("%i-%i-%i") % cv.year % cv.month % cv.day));
    sqlQuery->bindValue(":numerator", numerator);
    sqlQuery->bindValue("denominator", denominator);

    if (!sqlQuery->exec())
    {
      processErrorInformation();
    };
  };      // For loop.


}
