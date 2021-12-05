using System;
using System.Collections.Generic;
using System.Data;
using System.Data.SqlClient;

namespace SWO5.Dashboard.DAL.SQLe
{
    abstract class AbstractDao<T> : IDao<T>
    {
        protected const string CONNECTION_STRING = @"Data Source=(localdb)\MSSQLLocalDB;Initial Catalog=Covid;Integrated Security=True;Connect Timeout=30;Encrypt=False;TrustServerCertificate=False;ApplicationIntent=ReadWrite;MultiSubnetFailover=False";
        protected Type TypeInfo => typeof(T);

        private delegate IDbCommand ToSqlCommand(T entity, SqlConnection conn);
        protected abstract IDbCommand ToInsertCommand(T entity, SqlConnection conn);
        protected abstract IDbCommand ToUpdateCommand(T entity, SqlConnection conn);
        protected abstract IDbCommand ToDeleteCommand(T entity, SqlConnection conn);
        protected abstract T FromDataRecord(IDataRecord record);

        // ReadAll has been declared virtual, because tables like REPORT or DISTRICT require joins to get all relevant data.
        // This way there is a default implementation and the sub-classes can just override it
        public virtual IList<T> ReadAll()
        {
            IList<T> result = new List<T>();
            using (SqlConnection connection = new SqlConnection(CONNECTION_STRING))
            {
                connection.Open();
                string tableName = typeof(T).Name;
                string sqlCommand = $"SELECT * FROM [{tableName}]";
                using (IDbCommand command = new SqlCommand(sqlCommand, connection))
                {
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

        // same goes for ReadForIdentity. Report and District require an altered version.
        public virtual T ReadForIdentity(long id)
        {
            using (SqlConnection connection = new SqlConnection(CONNECTION_STRING))
            {
                connection.Open();
                string tableName = TypeInfo.Name;
                string sqlCommand = $"SELECT * FROM [{tableName}] WHERE id=@id";

                using (IDbCommand command = new SqlCommand(sqlCommand, connection))
                {
                    IDbDataParameter paramId = new SqlParameter("@id", SqlDbType.BigInt);
                    paramId.Value = id;
                    command.Parameters.Add(paramId);

                    IDataReader reader = command.ExecuteReader();
                    if (reader.Read())
                    {
                        IDataRecord record = reader;
                        return FromDataRecord(record);
                    }
                    else
                    {
                        return default(T);
                    }
                }
            }
        }
        

        // for DML statements = create Command delegate and forward to ExecuteDMLQuery
        public long Create(T entity)
        {
            return ExecuteDMLQuery(entity, ToInsertCommand);
        }

        public long Update(T entity)
        {
            return ExecuteDMLQuery(entity, ToUpdateCommand);
        }

        public bool Delete(T entity)
        {
            return ExecuteDMLQuery(entity, ToDeleteCommand) > 0;
        }

        public void Drop()
        {
            string tableName = typeof(T).Name;
            string sqlCommand = $"DELETE FROM [{tableName}]";
            using (SqlConnection connection = new SqlConnection(CONNECTION_STRING))
            {
                connection.Open();
                using (IDbCommand command = new SqlCommand(sqlCommand, connection))
                {
                    command.ExecuteNonQuery();
                }
            }
        }

        private long ExecuteDMLQuery(T entity, ToSqlCommand commandDelegate)
        {
            using (SqlConnection connection = new SqlConnection(CONNECTION_STRING))
            {
                connection.Open();
                using (IDbCommand command = commandDelegate(entity, connection))
                {
                    object result = command.ExecuteScalar();
                    return result != null ? Convert.ToInt64(result) : -1;
                }
            }
        }

        
    }
}
