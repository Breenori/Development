using SWO5.Dashboard.DAL;
using SWO5.Dashboard.Domain;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using SWO5.Dashboard.DAL.SQLe;
using System.IO;
using System.Security.Cryptography;

namespace SWO5.Dashboard.Logic
{
    public class SQLeBasedCovidDashboard : ICovidDashboard
    {
        private readonly IStateDao stateDao;
        private readonly IDistrictDao districtDao;
        private readonly IUserDao userDao;
        private readonly IReportDao reportDao;

        public SQLeBasedCovidDashboard()
        {
            IDaoFactory factory = new DaoFactorySQLe();
            stateDao = factory.StateDao;
            districtDao = factory.DistrictDao;
            userDao = factory.UserDao;
            reportDao = factory.ReportDao;
        }

        public IList<State> States => stateDao.ReadAll().ToList();

        public void FillFromCSV(string filename)
        {
            IList<District> districts = new List<District>();
            IList<Report> reports = new List<Report>();

            reportDao.Drop();
            districtDao.Drop();
 
            AddUser("admin", "geheim");

            using (StreamReader reader = new StreamReader(@$"{filename}"))
            {
                if (!reader.EndOfStream)
                {
                    reader.ReadLine();
                }

                while (!reader.EndOfStream)
                {
                    string line = reader.ReadLine();
                    string[] elements = line.Split(';');
                    DateTime reportTime = DateTime.Parse(elements[0]);
                    string districtName = elements[1];
                    long stateId = Convert.ToInt64(elements[2].Substring(0,1));
                    long districtId = Convert.ToInt64(elements[2]);
                    long districtPopulation = Convert.ToInt64(elements[3]);
                    long curInfected = Convert.ToInt64(elements[4]);
                    double incidence = Convert.ToDouble(elements[7]);
                    long curDeceased = Convert.ToInt64(elements[8]);
                    long curRecovered = Convert.ToInt64(elements[10]);

                    District curDistrict = new District
                    {
                        Id = districtId,
                        Name = districtName,
                        Population = districtPopulation,
                        ResponsibleState = new State { Id = stateId }
                    };

                    if (!districts.Contains(curDistrict))
                    {
                        districts.Add(curDistrict);
                    }

                    Report curReport = new Report
                    {
                        Date = reportTime,
                        ResponsibleDistrict = curDistrict,
                        Incidence = incidence,
                        Infected = curInfected,
                        Recovered = curRecovered,
                        Deceased = curDeceased,
                        // user for first inputs = Admin
                        FromUser = new User { Id = 0 }
                    };
                    reports.Add(curReport);
                }
            }


            foreach (District district in districts)
            {
                districtDao.Create(district);
            }
            foreach (Report report in reports)
            {
                reportDao.Create(report);
            }

            
        }

        public bool IsKnownDistrict(string district)
        {
            return reportDao.ReadAll().Any(r => r.ResponsibleDistrict.Name.Equals(district));
        }

        public bool IsKnownState(string state)
        {
            return reportDao.ReadAll().Any(r => r.ResponsibleDistrict.ResponsibleState.Name.Equals(state));
        }


        #region Data Querying
        public IList<District> FindDistrictsFor(string state)
        {
            return state != null ? districtDao.ReadForState(state) : districtDao.ReadAll().ToList();
        }

        public IList<Report> GetAllReports()
        {
            return reportDao.ReadAll().ToList();
        }

        public IList<Report> GetReportsForDistrict(string district)
        {
            return reportDao.FindReportsForDistrict(district);
        }

        public IList<Report> GetReportsForState(string state)
        {
            return reportDao.FindReportsForState(state);
        }
        #endregion

        #region AddMethods
        public State AddState(State state)
        {
            state.Id = stateDao.Create(state);
            return state;
        }
        public District AddDistrict(District district)
        {
            district.Id = districtDao.Create(district);
            return district;
        }
        public Report AddReport(Report report)
        {
            report.Id = reportDao.Create(report);
            return report;
        }
        public bool AddUser(string username, string password)
        {
            // To add a user, the name must be free
            if(!UserExists(username))
            {
                User newUser = new User { Name = username, Password = HashPassword(password) };
                return userDao.Create(newUser) != -1;
            }
            Console.WriteLine($"User '{username}' already exists.");
            return false;
        }
        #endregion

        #region UpdateMethods
        public bool UpdateState(State state)
        {
            return stateDao.Update(state) != -1;
        }
        public bool UpdateDistrict(District district)
        {
            return districtDao.Update(district) != -1;
        }
        public bool UpdateReport(Report report)
        {
            return reportDao.Update(report) != -1;
        }

        public bool UpdateUser(User updatedUser, string username, string password)
        {
            // can only update a user that exists
            if (UserExists(username))
            {
                User curUser = userDao.ReadAll().Where(u => u.Name.Equals(username)).Single();

                // the password needs to match, to update the user
                if (curUser.Password.Equals(HashPassword(password)))
                {
                    // also, the username needs to be free or the same
                    if (!UserExists(updatedUser.Name) || updatedUser.Name.Equals(username))
                    {
                        curUser.Name = updatedUser.Name;
                        curUser.Password = HashPassword(updatedUser.Password);
                        long updatedId = userDao.Update(curUser);

                        return true;
                    }
                    Console.WriteLine("This username is already taken.");
                    return false;
                }
            }
            Console.Write("Authentication failure: Wrong username or password.");
            return false;
        }
        #endregion

        #region RemoveMethods
        public bool RemoveState(State state)
        {
            return stateDao.Delete(state);
        }
        public bool RemoveDistrict(District district)
        {
            return districtDao.Delete(district);
        }
        public bool RemoveReport(Report report)
        {
            return reportDao.Delete(report);
        }
        public bool RemoveUser(string username, string password)
        {
            // can only remove existing users
            if (UserExists(username)) {
                User curUser = userDao.ReadAll().Where(u => u.Name.Equals(username)).Single();
                if (curUser.Password.Equals(HashPassword(password)))
                {
                    userDao.Delete(curUser);
                    return true;
                }
            }
            return false;
        }
        #endregion

        #region UserManagement
        public bool Login(string username, string password)
        {
            // Can only log in if the user exists
            if (UserExists(username))
            {
                string hashed = HashPassword(password);
                User foundUser = userDao.ReadAll().Where(u => u.Name.Equals(username)).Single();
                // the password needs to match if hashed
                if (foundUser.Password.Equals(HashPassword(password)))
                {
                    return true;
                }
            }
            return false;
        }
        private String HashPassword(string password)
        {
            // use SHA256 hash algorithm to store the passwords
            using (SHA256 mySHA256 = SHA256.Create())
            {
                byte[] bytes = mySHA256.ComputeHash(Encoding.UTF8.GetBytes(password));

                // Convert byte array to a string   
                StringBuilder builder = new StringBuilder();
                for (int i = 0; i < bytes.Length; i++)
                {
                    builder.Append(bytes[i].ToString("x2"));
                }

                return builder.ToString();
            }
        }
        private bool UserExists(string username) {
            return userDao.ReadAll().Any(u => u.Name.Equals(username)); ;
        }
        #endregion
    }

}
