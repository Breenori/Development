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
    class CountryDaoSQLe : AbstractDao<Country>, ICountryDao
    {
        public IList<Country> ReadForCurrencyType(CurrencyType currencyType)
        {
            IList<Country> result = new List<Country>();
            string selectCommand = $"SELECT id, name, code FROM {TypeInfo.Name} WHERE currency_id=@currency_id";
            using (SqlConnection connection = new SqlConnection(CONNECTION_STRING))
            {
                connection.Open();
                using (IDbCommand command = new SqlCommand(selectCommand, connection))
                {
                    IDbDataParameter paramInstant = new SqlParameter("@currency_id", SqlDbType.BigInt);
                    paramInstant.Value = currencyType.Id;
                    command.Parameters.Add(paramInstant);
                    
                    IDataReader reader = command.ExecuteReader();
                    while (reader.Read())
                    {
                        IDataRecord record = reader;
                        result.Add(FromDataRecord(record));
                    }
                }
            }
            return result;
        }

        protected override Country FromDataRecord(IDataRecord record)
        {
            return record.ToCountry();
        }

        protected override IDbCommand ToInsertCommand(Country element, SqlConnection connection)
        {
            string query = $"INSERT INTO {TypeInfo.Name} (name) VALUES (@name); SELECT SCOPE_IDENTITY()";
            IDbCommand command = new SqlCommand(query, connection);
            IDbDataParameter paramName = new SqlParameter("@name", SqlDbType.NVarChar);
            paramName.Value = element.Name;
            command.Parameters.Add(paramName);
            return command;
        }

        protected override IDbCommand ToUpdateCommand(Country element, SqlConnection connection)
        {
            string query = $"UPDATE {TypeInfo.Name} SET name = @name WHERE id = @id; SELECT id FROM {TypeInfo.Name} WHERE id =@id";
            IDbCommand command = new SqlCommand(query, connection);
            IDbDataParameter paramName = new SqlParameter("@name", SqlDbType.NVarChar);
            paramName.Value = element.Name;
            command.Parameters.Add(paramName);
            IDbDataParameter paramId = new SqlParameter("@id", SqlDbType.BigInt);
            paramId.Value = element.Id;
            command.Parameters.Add(paramId);
            return command;
        }
    }
}
