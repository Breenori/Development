using Microsoft.Data.SqlClient;
using SWO5.Currency.Domain;
using System;
using System.Collections.Generic;
using System.Data;
using System.Linq;
using System.Reflection;
using System.Text;
using System.Threading.Tasks;

namespace SWO5.Currency.DAL.SQLe
{
    class ExchangeRateDaoSQLe : AbstractDao<ExchangeRate>, IExchangeRateDao
    {
        public IList<ExchangeRate> FindExchangeRatesFor(Instant instant, string currencyCode)
        {
            IList<ExchangeRate> result = new List<ExchangeRate>();
            string tableName = TypeInfo.Name;
            string selectCommand = $"SELECT e.id as id, e.rate as rate, c.id as c_id, c.code as code, c.name as name FROM ExchangeRate e, CurrencyType c WHERE e.currency_id = c.id AND e.instant_id = @instant_id AND c.code=@code";
            using ( SqlConnection connection = new SqlConnection(CONNECTION_STRING))
            {
                connection.Open();
                using (IDbCommand command = new SqlCommand(selectCommand, connection))
                {
                    IDbDataParameter paramInstant = new SqlParameter("@instant_id", SqlDbType.BigInt);
                    paramInstant.Value = instant.Id;
                    command.Parameters.Add(paramInstant);
                    IDbDataParameter paramCode = new SqlParameter("@code", SqlDbType.NVarChar);
                    paramCode.Value = currencyCode;
                    command.Parameters.Add(paramCode);
                    IDataReader reader = command.ExecuteReader();
                    while(reader.Read())
                    {
                        IDataRecord record = reader;
                        ExchangeRate rate = record.ToExchangeRate();
                    }
                }
            }

            return result;
        }

        protected override ExchangeRate FromDataRecord(IDataRecord record)
        {
            return record.ToExchangeRate();
        }

        protected override IDbCommand ToInsertCommand(ExchangeRate entity, SqlConnection conn)
        {
            throw new NotImplementedException();
        }

        protected override IDbCommand ToUpdateCommand(ExchangeRate entity, SqlConnection conn)
        {
            throw new NotImplementedException();
        }
    }
}
