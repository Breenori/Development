using SWO5.Dashboard.Domain;
using System;
using System.Collections.Generic;
using System.Data;
using System.Data.SqlClient;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace SWO5.Dashboard.DAL.SQLe
{
    class UserDaoSQLe : AbstractDao<User>, IUserDao
    {
        protected override User FromDataRecord(IDataRecord record)
        {
            return record.ToUser();
        }

        public override User ReadForIdentity(long id)
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
                        return null;
                    }
                }
            }
        }

        protected override IDbCommand ToInsertCommand(User entity, SqlConnection conn)
        {
            string query = $"INSERT INTO [{TypeInfo.Name}] (name, password) VALUES (@name, @password); SELECT SCOPE_IDENTITY()";

            IDbCommand command = new SqlCommand(query, conn);
            IDbDataParameter paramId = new SqlParameter("@id", SqlDbType.BigInt);
            paramId.Value = entity.Id;
            command.Parameters.Add(paramId);

            IDbDataParameter paramName = new SqlParameter("@name", SqlDbType.NVarChar);
            paramName.Value = entity.Name;
            command.Parameters.Add(paramName);

            IDbDataParameter paramPassword = new SqlParameter("@password", SqlDbType.NVarChar);
            paramPassword.Value = entity.Password;
            command.Parameters.Add(paramPassword);

            return command;
        }

        protected override IDbCommand ToUpdateCommand(User entity, SqlConnection conn)
        {
            string query = $"UPDATE [{TypeInfo.Name}] SET name = @name, password = @password WHERE id = @id; SELECT id FROM [{TypeInfo.Name}] WHERE id = @id";
            IDbCommand command = new SqlCommand(query, conn);

            IDbDataParameter paramId = new SqlParameter("@id", SqlDbType.BigInt);
            paramId.Value = entity.Id;
            command.Parameters.Add(paramId);

            IDbDataParameter paramName = new SqlParameter("@name", SqlDbType.NVarChar);
            paramName.Value = entity.Name;
            command.Parameters.Add(paramName);

            IDbDataParameter paramPassword = new SqlParameter("@password", SqlDbType.NVarChar);
            paramPassword.Value = entity.Password;
            command.Parameters.Add(paramPassword);

            return command;
        }

        protected override IDbCommand ToDeleteCommand(User entity, SqlConnection conn)
        {
            string query = $"DELETE FROM [{TypeInfo.Name}] WHERE id=@id and password=@password";
            IDbCommand command = new SqlCommand(query, conn);

            IDbDataParameter paramId = new SqlParameter("@id", SqlDbType.BigInt);
            paramId.Value = entity.Id;
            command.Parameters.Add(paramId);

            IDbDataParameter paramPassword = new SqlParameter("@password", SqlDbType.NVarChar);
            paramPassword.Value = entity.Password;
            command.Parameters.Add(paramPassword);

            return command;
        }

    }
}
