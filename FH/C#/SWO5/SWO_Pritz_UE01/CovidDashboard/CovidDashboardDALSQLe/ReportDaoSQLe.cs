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
    class ReportDaoSQLe : AbstractDao<Report>, IReportDao
    {
        // returns all reports for a given district
        public IList<Report> FindReportsForDistrict(string district)
        {
            string tableName = TypeInfo.Name;
            IList<Report> result = new List<Report>();
            string selectCommand =  $"SELECT r.id report_id, d.id district_id, r.report_date report_date, d.population district_population, d.name district_name, s.id state_id, s.name state_name, incidence, num_infected, num_recovered, num_deceased, u.id user_id, u.name user_name, u.password user_password" +
                                    $" FROM {tableName} r" +
                                    $" JOIN district d ON r.district_id=d.id" +
                                    $" JOIN state s ON d.state_id=s.id" +
                                    $" JOIN [user] u ON r.user_id=u.id" +
                                    $" WHERE d.name=@district_name";
            using (SqlConnection connection = new SqlConnection(CONNECTION_STRING))
            {
                connection.Open();
                using (IDbCommand command = new SqlCommand(selectCommand, connection))
                {
                    IDbDataParameter paramDistrictName = new SqlParameter("@district_name", SqlDbType.NVarChar);
                    paramDistrictName.Value = district;
                    command.Parameters.Add(paramDistrictName);

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
        public IList<Report> FindReportsForState(string state)
        {
            string tableName = TypeInfo.Name;
            IList<Report> result = new List<Report>();
            string selectCommand = $"SELECT r.id report_id, r.report_date report_date, d.id district_id, d.population district_population, d.name district_name, s.id state_id, s.name state_name, incidence, num_infected, num_recovered, num_deceased, u.id user_id, u.name user_name, u.password user_password" +
                                    $" FROM {tableName} r" +
                                    $" JOIN district d ON r.district_id=d.id" +
                                    $" JOIN state s ON d.state_id=s.id" +
                                    $" JOIN [user] u ON r.user_id=u.id" +
                                    $" WHERE s.name=@state_name";
            using (SqlConnection connection = new SqlConnection(CONNECTION_STRING))
            {
                connection.Open();
                using (IDbCommand command = new SqlCommand(selectCommand, connection))
                {
                    IDbDataParameter paramStateName = new SqlParameter("@state_name", SqlDbType.NVarChar);
                    paramStateName.Value = state;
                    command.Parameters.Add(paramStateName);

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

        protected override Report FromDataRecord(IDataRecord record)
        {
            return record.ToReport();
        }

        public override Report ReadForIdentity(long id)
        {
            using (SqlConnection connection = new SqlConnection(CONNECTION_STRING))
            {
                connection.Open();
                string tableName = TypeInfo.Name;
                string sqlCommand = $"SELECT r.id report_id, r.report_date report_date, d.id district_id, d.population district_population, d.name district_name, s.id state_id, s.name state_name, incidence, num_infected, num_recovered, num_deceased, u.id user_id, u.name user_name, u.password user_password" +
                                    $" FROM {tableName} r" +
                                    $" JOIN district d ON r.district_id=d.id" +
                                    $" JOIN state s ON d.state_id=s.id" +
                                    $" JOIN [user] u ON r.user_id=u.id" +
                                    $" WHERE r.id=@id";

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

        protected override IDbCommand ToInsertCommand(Report entity, SqlConnection conn)
        {
            string query =  $"INSERT INTO {TypeInfo.Name} (report_date, district_id, incidence, num_infected, num_recovered, num_deceased, user_id)" +
                            $" VALUES (@report_date, @district_id, @incidence, @num_infected, @num_recovered, @num_deceased, @user_id); SELECT SCOPE_IDENTITY()";

            IDbCommand command = new SqlCommand(query, conn);

            IDbDataParameter paramDate = new SqlParameter("@report_date", SqlDbType.DateTime);
            paramDate.Value = entity.Date;
            command.Parameters.Add(paramDate);

            IDbDataParameter paramDistrictId = new SqlParameter("@district_id", SqlDbType.BigInt);
            paramDistrictId.Value = entity.ResponsibleDistrict.Id;
            command.Parameters.Add(paramDistrictId);

            IDbDataParameter paramIncidence = new SqlParameter("@incidence", SqlDbType.Float);
            paramIncidence.Value = entity.Incidence;
            command.Parameters.Add(paramIncidence);

            IDbDataParameter paramInfected = new SqlParameter("@num_infected", SqlDbType.BigInt);
            paramInfected.Value = entity.Infected;
            command.Parameters.Add(paramInfected);

            IDbDataParameter paramRecovered = new SqlParameter("@num_recovered", SqlDbType.BigInt);
            paramRecovered.Value = entity.Recovered;
            command.Parameters.Add(paramRecovered);

            IDbDataParameter paramDeceased = new SqlParameter("@num_deceased", SqlDbType.BigInt);
            paramDeceased.Value = entity.Deceased;
            command.Parameters.Add(paramDeceased);

            IDbDataParameter paramUserId = new SqlParameter("@user_id", SqlDbType.BigInt);
            paramUserId.Value = entity.FromUser.Id;
            command.Parameters.Add(paramUserId);

            return command;
        }

        protected override IDbCommand ToUpdateCommand(Report entity, SqlConnection conn)
        {
            string query =  $"UPDATE {TypeInfo.Name} SET district_id=@district_id," +
                            $" incidence=@incidence, num_infected=@num_infected, num_recovered=@num_recovered, num_deceased=@num_deceased, user_id=@user_id " +
                            $" WHERE id = @id; SELECT id FROM {TypeInfo.Name} WHERE id = @id";
            IDbCommand command = new SqlCommand(query, conn);

            IDbDataParameter paramId = new SqlParameter("@id", SqlDbType.BigInt);
            paramId.Value = entity.Id;
            command.Parameters.Add(paramId);

            IDbDataParameter paramDate = new SqlParameter("@report_date", SqlDbType.DateTime);
            paramDate.Value = entity.Date;
            command.Parameters.Add(paramDate);

            IDbDataParameter paramDistrictId = new SqlParameter("@district_id", SqlDbType.BigInt);
            paramDistrictId.Value = entity.ResponsibleDistrict.Id;
            command.Parameters.Add(paramDistrictId);

            IDbDataParameter paramIncidence = new SqlParameter("@incidence", SqlDbType.Float);
            paramIncidence.Value = entity.Incidence;
            command.Parameters.Add(paramIncidence);

            IDbDataParameter paramInfected = new SqlParameter("@num_infected", SqlDbType.BigInt);
            paramInfected.Value = entity.Infected;
            command.Parameters.Add(paramInfected);

            IDbDataParameter paramRecovered = new SqlParameter("@num_recovered", SqlDbType.BigInt);
            paramRecovered.Value = entity.Recovered;
            command.Parameters.Add(paramRecovered);

            IDbDataParameter paramDeceased = new SqlParameter("@num_deceased", SqlDbType.BigInt);
            paramDeceased.Value = entity.Deceased;
            command.Parameters.Add(paramDeceased);

            IDbDataParameter paramUserId = new SqlParameter("@user_id", SqlDbType.BigInt);
            paramUserId.Value = entity.FromUser.Id;
            command.Parameters.Add(paramUserId);

            return command;
        }

        protected override IDbCommand ToDeleteCommand(Report entity, SqlConnection conn)
        {
            string query = $"DELETE FROM {TypeInfo.Name} WHERE id=@id";
            IDbCommand command = new SqlCommand(query, conn);

            IDbDataParameter paramId = new SqlParameter("@id", SqlDbType.BigInt);
            paramId.Value = entity.Id;
            command.Parameters.Add(paramId);

            return command;
        }

        public override IList<Report> ReadAll()
        {
            IList<Report> result = new List<Report>();
            using (SqlConnection connection = new SqlConnection(CONNECTION_STRING))
            {
                connection.Open();
                string sqlCommand = $"SELECT r.id report_id, r.report_date report_date, d.id district_id, d.population district_population, d.name district_name, s.id state_id, s.name state_name, incidence, num_infected, num_recovered, num_deceased, u.id user_id, u.name user_name, u.password user_password" +
                                    $" FROM report r" +
                                    $" JOIN district d ON r.district_id=d.id" +
                                    $" JOIN state s ON d.state_id=s.id" +
                                    $" JOIN [user] u ON r.user_id=u.id";
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
