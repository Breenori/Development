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
    class InstantDaoSQLe : AbstractDao<Instant>, IInstantDao
    {
        public Instant FindCurrentInstant()
        {
            string tableName = TypeInfo.Name;
            string selectCommand = $"SELECT TOP 1 id, time FROM {tableName} ORDER BY time DESC";
            using (SqlConnection connection = new SqlConnection( CONNECTION_STRING ) )
            {
                connection.Open();
                using ( IDbCommand command = new SqlCommand( selectCommand, connection ))
                {
                    IDataReader reader = command.ExecuteReader();
                    if( reader.Read() )
                    {
                        IDataRecord record = reader;
                        return record.ToInstant();
                    } else
                    {
                        return null;
                    }
                }
            }
        }

        protected override Instant FromDataRecord(IDataRecord record)
        {
            return record.ToInstant();
        }

        protected override IDbCommand ToInsertCommand(Instant element, SqlConnection connection)
        {
            string query = $"INSERT INTO {TypeInfo.Name} (time) VALUES( @time ); SELECT SCOPE_IDENTITY()";
            SqlCommand command = new SqlCommand(query, connection);
            IDbDataParameter parameter = new SqlParameter("@time", SqlDbType.DateTime);
            parameter.Value = element.Time;
            command.Parameters.Add(parameter);
            return command;
        }

        protected override IDbCommand ToUpdateCommand(Instant element, SqlConnection connection)
        {
            string query = $"UPDATE {TypeInfo.Name} SET time = @time WHERE id = @id; SELECT SCOPE_IDENTITY()";
            SqlCommand command = new SqlCommand(query, connection);
            IDbDataParameter parameter = new SqlParameter("@time", SqlDbType.DateTime);
            parameter.Value = element.Time;
            command.Parameters.Add(parameter);
            parameter = new SqlParameter("@id", SqlDbType.BigInt);
            parameter.Value = element.Id;
            command.Parameters.Add(parameter);
            return command;
        }
    }
}
