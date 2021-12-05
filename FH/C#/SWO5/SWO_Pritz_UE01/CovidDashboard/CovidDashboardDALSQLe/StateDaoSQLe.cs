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
    class StateDaoSQLe : AbstractDao<State>, IStateDao
    {
        protected override State FromDataRecord(IDataRecord record)
        {
            return record.ToState();
        }

        protected override IDbCommand ToInsertCommand(State entity, SqlConnection conn)
        {
            string query = $"INSERT INTO {TypeInfo.Name} (name) VALUES (@name); SELECT SCOPE_IDENTITY()";

            IDbCommand command = new SqlCommand(query, conn);

            IDbDataParameter paramName = new SqlParameter("@name", SqlDbType.NVarChar);
            paramName.Value = entity.Name;
            command.Parameters.Add(paramName);

            return command;
        }

        protected override IDbCommand ToUpdateCommand(State entity, SqlConnection conn)
        {
            string query = $"UPDATE {TypeInfo.Name} SET name = @name WHERE id = @id; SELECT id FROM {TypeInfo.Name} WHERE id =@id";
            IDbCommand command = new SqlCommand(query, conn);

            IDbDataParameter paramName = new SqlParameter("@name", SqlDbType.NVarChar);
            paramName.Value = entity.Name;
            command.Parameters.Add(paramName);

            IDbDataParameter paramId = new SqlParameter("@id", SqlDbType.BigInt);
            paramId.Value = entity.Id;
            command.Parameters.Add(paramId);

            return command;
        }


        protected override IDbCommand ToDeleteCommand(State entity, SqlConnection conn)
        {
            string query = $"DELETE FROM {TypeInfo.Name} WHERE id=@id";
            IDbCommand command = new SqlCommand(query, conn);

            IDbDataParameter paramId = new SqlParameter("@id", SqlDbType.BigInt);
            paramId.Value = entity.Id;
            command.Parameters.Add(paramId);

            return command;
        }
    }
}
