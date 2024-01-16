using Microsoft.Data.SqlClient;
using SWO5.Currency.Domain;
using System;
using System.Collections.Generic;
using System.Data;
using System.Linq;
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
            string selectCommand = $"SELECT e.id as id, e.rate as rate, c.id as c_id, c.code as code, c.name as name  FROM ExchangeRate e, CurrencyType c WHERE e.currency_id = c.id AND e.instant_id = @instant_id AND c.code = @code";
            using ( SqlConnection connection = new SqlConnection( CONNECTION_STRING ) )
            {
                connection.Open();
                using( IDbCommand command = new SqlCommand( selectCommand, connection ) )
                {
                    IDbDataParameter paramInstant = new SqlParameter("@instant_id", SqlDbType.BigInt);
                    paramInstant.Value = instant.Id;
                    command.Parameters.Add(paramInstant);
                    IDbDataParameter paramCode = new SqlParameter("@code", SqlDbType.NVarChar);
                    paramCode.Value = currencyCode;
                    command.Parameters.Add(paramCode);
                    IDataReader reader = command.ExecuteReader();
                    while( reader.Read() )
                    {
                        IDataRecord record = reader;
                        ExchangeRate rate = record.ToExchangeRate();
                        CurrencyType currencyType = new CurrencyType
                        {
                            Id = (long)record["c_id"],
                            Code = (string)record["code"],
                            Name = (string)record["name"]
                        };
                        rate.CurrencyType = currencyType;
                        result.Add( rate );

                    }
                }
            }
            return result;
        }

        public IList<Tuple<DateTime, ExchangeRate>> FindExchangeRatesFor(string currencyCode)
        {
            IList<Tuple<DateTime, ExchangeRate>> result = new List<Tuple<DateTime, ExchangeRate>>();
            using (SqlConnection connection = new SqlConnection(CONNECTION_STRING))
            {
                connection.Open();
                String tableName = TypeInfo.Name; // returns type of implementing subclasses
                String selectCommand = $"SELECT i.time as time, e.id as id, e.rate as rate, c.id as c_id, c.code as code, c.name as name FROM ExchangeRate e, CurrencyType c, Instant i WHERE e.currency_id = c.id AND e.instant_id = i.id AND c.code = @code ORDER BY i.time ASC";
                using (IDbCommand command = new SqlCommand(selectCommand, connection))
                {
                    IDbDataParameter parameter = new SqlParameter("@code", SqlDbType.NVarChar);
                    command.Parameters.Add(parameter);
                    parameter.Value = currencyCode;
                    IDataReader reader = command.ExecuteReader();
                    while (reader.Read())
                    {
                        IDataRecord record = reader;
                        ExchangeRate rate = FromDataRecord(record);
                        CurrencyType currencyType = new CurrencyType()
                        {
                            Id = (long)reader["c_id"],
                            Code = (string)reader["code"],
                            Name = (string)reader["name"]
                        };
                        rate.CurrencyType = currencyType;
                        result.Add(new Tuple<DateTime, ExchangeRate>((DateTime)reader["time"], rate));
                    }
                } // cmd.Dispose() --> cmd.Close()
            } // connection.Dispose() --> connection.Close()
            return result;
        }



        protected override ExchangeRate FromDataRecord(IDataRecord record)
        {
            return record.ToExchangeRate();
        }

        protected override IDbCommand ToInsertCommand(ExchangeRate element, SqlConnection connection)
        {
            string query = $"INSERT INTO {TypeInfo.Name} (rate) VALUES( @rate ); SELECT SCOPE_IDENTITY()";
            SqlCommand command = new SqlCommand(query, connection);
            IDbDataParameter parameter = new SqlParameter("@rate", SqlDbType.Decimal);
            parameter.Value = element.Rate;
            command.Parameters.Add(parameter);
            return command;
        }

        protected override IDbCommand ToUpdateCommand(ExchangeRate element, SqlConnection connection)
        {
            string query = $"UPDATE {TypeInfo.Name} SET rate = @rate WHERE id = @id; ; SELECT id FROM {TypeInfo.Name} WHERE id =@id";
            SqlCommand command = new SqlCommand(query, connection);
            IDbDataParameter parameter = new SqlParameter("@rate", SqlDbType.Decimal);
            parameter.Value = element.Rate;
            command.Parameters.Add(parameter);
            parameter = new SqlParameter("@id", SqlDbType.BigInt);
            parameter.Value = element.Id;
            command.Parameters.Add(parameter);
            return command;
        }
    }
}
