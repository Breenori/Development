using System;
using System.Collections.Generic;
using SWO5.Dashboard.Domain;

namespace SWO5.Dashboard.Logic
{
    public interface ICovidDashboard
    {
        bool IsKnownState(string state);
        bool IsKnownDistrict(string district);

        public bool Login(string username, string password);
        public bool AddUser(string username, string password);
        public bool RemoveUser(string username, string password);
        public bool UpdateUser(User updatedUser, string username, string password);

        public IList<State> States { get; }
        public IList<District> FindDistrictsFor(string state);

        public IList<Report> GetAllReports();
        public IList<Report> GetAllReports(DateTime from, DateTime to);
        public IList<Report> GetReportsForDistrict(string district);
        public IList<Report> GetReportsForDistrict(string district, DateTime from, DateTime to);
        public IList<Report> GetReportsForState(string state);
        public IList<Report> GetReportsForState(string state, DateTime from, DateTime to);

        public Report AddReport(Report report);
        public bool RemoveReport(Report report);
        public bool UpdateReport(Report report);

        public void FillFromCSV(string filename);

    }
}
