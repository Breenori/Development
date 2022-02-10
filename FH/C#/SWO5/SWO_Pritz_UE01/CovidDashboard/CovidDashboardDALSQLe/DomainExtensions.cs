using SWO5.Dashboard.Domain;
using System;
using System.Collections.Generic;
using System.Data;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace SWO5.Dashboard.DAL.SQLe
{
    static class DomainExtensions
    {
        public static State ToState(this IDataRecord record)
        {
            return new State
            {
                Id = (long)record["id"],
                Name = (string)record["name"]
            };
        }

        public static District ToDistrict(this IDataRecord record)
        {
            return new District
            {
                Id = (long)record["district_id"],
                Name = (string)record["district_name"],
                Population = (long)record["district_population"],
                ResponsibleState = new State { Id = (long)record["state_id"], Name = (string)record["state_name"] }
            };
        }

        public static User ToUser(this IDataRecord record)
        {
            return new User
            {
                Id = (long)record["id"],
                Name = (string)record["name"],
                Password = (string)record["password"]
            };
        }

        public static Report ToReport(this IDataRecord record)
        {
            return new Report
            {
                Id = (long)record["report_id"],
                ResponsibleDistrict = new District
                {
                    Id = (long)record["district_id"],
                    Name = (string)record["district_name"],
                    Population = (long)record["district_population"],
                    ResponsibleState = new State
                    {
                        Id = (long)record["state_id"],
                        Name = (string)record["state_name"]
                    },
                },
                Date = (DateTime)record["report_date"],
                Incidence = (double)record["incidence"],
                Infected = (long)record["num_infected"],
                Recovered = (long)record["num_recovered"],
                Deceased = (long)record["num_deceased"],
                FromUser = new User
                {
                    Id = (long)record["user_id"],
                    Name = (string)record["user_name"],
                    Password = (string)record["user_password"]
                }
            };
        }
    }
}
