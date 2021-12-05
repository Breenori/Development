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
    class DistrictDaoSQLe : AbstractDao<District>, IDistrictDao
    {
        protected override District FromDataRecord(IDataRecord record)
        {
            return record.ToDistrict();
        }

        public override District ReadForIdentity(District entity)
        {
            using (SqlConnection connection = new SqlConnection(CONNECTION_STRING))
            {
                connection.Open();
                string tableName = TypeInfo.Name;
                string sqlCommand = $"SELECT d.id district_id, d.name district_name, d.population district_population, s.id state_id, s.name state_name" +
                                    $" FROM {tableName} d" +
                                    $" JOIN state s ON s.id=d.state_id" +
                                    $" WHERE d.id=@id";

                using (IDbCommand command = new SqlCommand(sqlCommand, connection))
                {
                    IDbDataParameter paramId = new SqlParameter("@id", SqlDbType.BigInt);
                    paramId.Value = entity.Id;
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

        protected override IDbCommand ToInsertCommand(District entity, SqlConnection conn)
        {
            string query = $"INSERT INTO {TypeInfo.Name} (id, name, population, state_id) VALUES (@id, @name, @population, @state_id); SELECT id FROM {TypeInfo.Name} WHERE id=@id";

            IDbCommand command = new SqlCommand(query, conn);
            IDbDataParameter paramId = new SqlParameter("@id", SqlDbType.BigInt);
            paramId.Value = entity.Id;
            command.Parameters.Add(paramId);

            IDbDataParameter paramName = new SqlParameter("@name", SqlDbType.NVarChar);
            paramName.Value = entity.Name;
            command.Parameters.Add(paramName);

            IDbDataParameter paramPopulation = new SqlParameter("@population", SqlDbType.BigInt);
            paramPopulation.Value = entity.Population;
            command.Parameters.Add(paramPopulation);

            IDbDataParameter paramStateId = new SqlParameter("@state_id", SqlDbType.BigInt);
            paramStateId.Value = entity.ResponsibleState.Id;
            command.Parameters.Add(paramStateId);

            return command;
        }

        protected override IDbCommand ToUpdateCommand(District entity, SqlConnection conn)
        {
            string query = $"UPDATE {TypeInfo.Name} SET name = @name, population = @population WHERE id = @id AND state_id = @state_id; " +
                            $"SELECT id FROM {TypeInfo.Name} WHERE id = @id AND state_id = @state_id";
            IDbCommand command = new SqlCommand(query, conn);

            IDbDataParameter paramName = new SqlParameter("@name", SqlDbType.NVarChar);
            paramName.Value = entity.Name;
            command.Parameters.Add(paramName);

            IDbDataParameter paramId = new SqlParameter("@id", SqlDbType.BigInt);
            paramId.Value = entity.Id;
            command.Parameters.Add(paramId);

            IDbDataParameter paramPopulation = new SqlParameter("@population", SqlDbType.BigInt);
            paramPopulation.Value = entity.Population;
            command.Parameters.Add(paramPopulation);

            IDbDataParameter paramStateId = new SqlParameter("@state_id", SqlDbType.BigInt);
            paramStateId.Value = entity.ResponsibleState.Id;
            command.Parameters.Add(paramStateId);

            return command;
        }

        protected override IDbCommand ToDeleteCommand(District entity, SqlConnection conn)
        {
            string query = $"DELETE FROM {TypeInfo.Name} WHERE id=@id AND state_id=@state_id";
            IDbCommand command = new SqlCommand(query, conn);

            IDbDataParameter paramId = new SqlParameter("@id", SqlDbType.BigInt);
            paramId.Value = entity.Id;
            command.Parameters.Add(paramId);

            IDbDataParameter paramStateId = new SqlParameter("@state_id", SqlDbType.BigInt);
            paramStateId.Value = entity.ResponsibleState.Id;
            command.Parameters.Add(paramStateId);

            return command;
        }

        public IList<District> ReadForState(State state)
        {
            string tableName = TypeInfo.Name;
            IList<District> result = new List<District>();
            string selectCommand =  $"SELECT d.id district_id, d.name district_name, d.population district_population, s.id state_id, s.name state_name" +
                                    $" FROM {tableName} d" +
                                    $" JOIN state s ON s.id=d.state_id WHERE d.state_id=@state_id";
            using (SqlConnection connection = new SqlConnection(CONNECTION_STRING))
            {
                connection.Open();
                using (IDbCommand command = new SqlCommand(selectCommand, connection))
                {
                    IDbDataParameter paramStateId = new SqlParameter("@state_id", SqlDbType.BigInt);
                    paramStateId.Value = state.Id;
                    command.Parameters.Add(paramStateId);

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

        public override IList<District> ReadAll()
        {
            IList<District> result = new List<District>();
            using (SqlConnection connection = new SqlConnection(CONNECTION_STRING))
            {
                connection.Open();
                string sqlCommand = $"SELECT d.id district_id, d.name district_name, d.population district_population, s.id state_id, s.name state_name" +
                                    $" FROM district d" +
                                    $" JOIN state s ON s.id=d.state_id";
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
    }
}
