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
    class CurrencyTypeDaoSQLe : AbstractDao<CurrencyType>, ICurrencyTypeDao
    {
        protected override CurrencyType FromDataRecord(IDataRecord record)
        {
            // Version 1:
            /*return new CurrencyType { Id = (long)record["id"], 
                                      Code = (string)record["code"], 
                                      Name = (string)record["name"] }; */
            // Version 2: Extension Method
            return record.ToCurrencyType();
        }

        protected override IDbCommand ToInsertCommand(CurrencyType entity, SqlConnection conn)
        {
            string sqlCommand = $"INSERT INTO CurrencyType (code, name) VALUES (@code, @name); SELECT SCOPE_IDENTITY()";
            IDbCommand command = new SqlCommand(sqlCommand, conn);
            IDbDataParameter paramCode = new SqlParameter("@code", SqlDbType.NVarChar);
            IDbDataParameter paramName = new SqlParameter("@name", SqlDbType.NVarChar);
            paramCode.Value = entity.Code;
            paramName.Value = entity.Name;
            command.Parameters.Add(paramCode);
            command.Parameters.Add(paramName);
            return command;
        }

        protected override IDbCommand ToUpdateCommand(CurrencyType entity, SqlConnection conn)
        {
            string sqlCommand = $"UPDATE CurrencyType set code=@code, name=@name WHERE ID = @id; SELECT id FROM CurrencyType WHERE id=@id";
            IDbCommand command = new SqlCommand(sqlCommand, conn);
            IDbDataParameter paramId = new SqlParameter("@id", SqlDbType.BigInt);
            IDbDataParameter paramCode = new SqlParameter("@code", SqlDbType.NVarChar);
            IDbDataParameter paramName = new SqlParameter("@name", SqlDbType.NVarChar);
            paramId.Value = entity.Id;
            paramCode.Value = entity.Code;
            paramName.Value = entity.Name;
            command.Parameters.Add(paramId); 
            command.Parameters.Add(paramCode);
            command.Parameters.Add(paramName);
            return command;
        }
    }
}
