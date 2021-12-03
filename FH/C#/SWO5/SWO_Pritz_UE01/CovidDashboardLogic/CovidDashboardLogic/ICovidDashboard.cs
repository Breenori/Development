using System;
using System.Collections.Generic;
using SWO5.Dashboard.Domain;

namespace SWO5.Dashboard.Logic
{
    public interface ICovidDashboard
    {
        bool IsKnownState(string state);
        bool IsKnownDistrict(string district);

        public User Login(string username, string password);
        public bool AddUser(string username, string password);
        public bool RemoveUser(string username, string password);
        public bool UpdateUser(string username, string password);  

        public IList<State> States { get; }

        public IList<District> FindDistrictsFor(State state);
        public IList<Report> GetReports(string district);

        public Report AddReport(Report report);
        public bool RemoveReport(Report report);
        public Report UpdateReport(Report report);

    }
}
