using System;
using System.Collections.Generic;
using SWO5.Dashboard.Domain;

namespace SWO5.Dashboard.Logic
{
    public interface ICovidDashboard
    {
        bool IsKnownState(string state);
        bool IsKnownDistrict(string district);

        public State AddState(State state);
        public bool RemoveState(State state);
        public bool UpdateState(State state);

        public District AddDistrict(District district);
        public bool RemoveDistrict(District district);
        public bool UpdateDistrict(District district);

        public bool Login(string username, string password);
        public bool AddUser(string username, string password);
        public bool RemoveUser(string username, string password);
        public bool UpdateUser(User updatedUser, string username, string password);

        public Report AddReport(Report report);
        public bool RemoveReport(Report report);
        public bool UpdateReport(Report report);

        public IList<State> States { get; }
        public IList<District> FindDistrictsFor(string state);

        public IList<Report> GetAllReports();
        public IList<Report> GetReportsForDistrict(string district);
        public IList<Report> GetReportsForState(string state);

        public void FillFromCSV(string filename);

    }
}
