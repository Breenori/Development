using System;
using System.Collections.Generic;
using System.Data;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Microsoft.Data.Sql;
using Microsoft.Data.SqlClient;

namespace SWO5.Currency.DAL.SQLe
{
    abstract class AbstractDao<T> : IDao<T>
    {
        protected const string CONNECTION_STRING = @"Data Source=(localdb)\MSSQLLocalDB;Initial Catalog=master;Integrated Security=True;Connect Timeout=30;Encrypt=False;TrustServerCertificate=False;ApplicationIntent=ReadWrite;MultiSubnetFailover=False";
        private delegate IDbCommand ToSqlCommand(T entity, SqlConnection conn);
        protected abstract IDbCommand ToInsertCommand(T entity, SqlConnection conn);
        protected abstract IDbCommand ToUpdateCommand(T entity, SqlConnection conn);
        protected abstract T FromDataRecord(IDataRecord record);
        
        public long Create(T entity)
        {
            return ExecuteDMLQuery(entity, ToInsertCommand);
        }

        public bool Delete(long id)
        {
            string tableName = typeof(T).Name;
            string sqlCommand = $"DELETE FROM {tableName} WHERE id=@id";
            using (SqlConnection connection = new SqlConnection(CONNECTION_STRING))
            {
                connection.Open();
                using(IDbCommand command = new SqlCommand(sqlCommand, connection))
                {
                    IDbDataParameter paramId = new SqlParameter("@id", SqlDbType.BigInt);
                    paramId.Value = id;
                    command.Parameters.Add(paramId);
                    return command.ExecuteNonQuery() > 0;
                }
            }
        }

        public IList<T> ReadAll()
        {
            IList<T> result = new List<T>();
            using (SqlConnection connection = new SqlConnection(CONNECTION_STRING))
            {
                connection.Open();
                string tableName = typeof(T).Name;
                string sqlCommand = $"SELECT * FROM {tableName}";
                using (IDbCommand command = new SqlCommand(sqlCommand, connection))
                {
                    IDataReader reader = command.ExecuteReader();
                    while(reader.Read())
                    {
                        IDataRecord record = reader;
                        result.Add(FromDataRecord(record));
                    }
                }
            }
            return result;
        }

        public T ReadForIdentity(long identity)
        {
            using (SqlConnection connection = new SqlConnection(CONNECTION_STRING))
            {
                connection.Open();
                string tableName = typeof(T).Name;
                string sqlCommand = $"SELECT * FROM {tableName} WHERE id=@id";
                using (IDbCommand command = new SqlCommand(sqlCommand, connection))
                {
                    IDbDataParameter paramId = new SqlParameter("@id", SqlDbType.BigInt);
                    paramId.Value = identity;
                    command.Parameters.Add(paramId);

                    IDataReader reader = command.ExecuteReader();
                    if(reader.Read())
                    {
                        IDataRecord record = reader;
                        return FromDataRecord(record);
                    } else
                    {
                        return default(T);
                    }
                }
            }
        }

        public long Update(T entity)
        {
            throw new NotImplementedException();
        }

        private long ExecuteDMLQuery(T entity, ToSqlCommand commandDelegate)
        {
            using (SqlConnection connection = new SqlConnection(CONNECTION_STRING))
            {
                connection.Open();
                using (IDbCommand command = commandDelegate(entity, connection))
                {
                    return Convert.ToInt64(command.ExecuteScalar());
                }
            }
        }
    }
}
