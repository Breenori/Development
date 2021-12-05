using Microsoft.VisualStudio.TestTools.UnitTesting;
using SWO5.Dashboard.Domain;
using SWO5.Dashboard.Logic;
using System;
using System.Collections.Generic;
using System.Linq;

namespace SWO5.Dashboard.Test
{
    [TestClass]
    public class CovidDashboardTest
    {
        ICovidDashboard dashboard;
        IList<User> test_users;
        IList<Report> test_reports;

        [TestInitialize]
        public void Initialize()
        {
            dashboard = CovidDashboardFactory.CreateCovidDashboard();

            //dashboard.FillFromCSV(@"../../../../CovidFaelle_Timeline_GKZ.csv");


            // CREATE TEST DATA:
            test_users = new List<User>();
            test_users.Add(new User { Id = 0, Name = "admin", Password = "geheim" });
            test_users.Add(new User { Name = "AddUser", Password = "test_adduser" });
            test_users.Add(new User { Name = "RemoveUser", Password = "test_removeuser" });
            test_users.Add(new User { Name = "UpdateUser", Password = "test_updateuser" });
            test_users.Add(new User { Name = "UpdateTester", Password = "Alligator3" });

            // make sure that the users can be added, removed or updated
            dashboard.RemoveUser(test_users[1].Name, test_users[1].Password);
            dashboard.AddUser(test_users[2].Name, test_users[2].Password);
            dashboard.AddUser(test_users[3].Name, test_users[3].Password);
            dashboard.RemoveUser(test_users[4].Name, test_users[4].Password);

            test_reports = new List<Report>();
            test_reports.Add(new Report
            {
                Date = DateTime.Now,
                ResponsibleDistrict = dashboard.FindDistrictsFor(null).Where(d => d.Name.Equals("Freistadt")).Single(),
                Incidence = 12.7,
                Infected = 420,
                Recovered = 1337,
                Deceased = 20,
                FromUser = test_users[0]
            });
            test_reports.Add(new Report
            {
                Date = DateTime.Now,
                ResponsibleDistrict = dashboard.FindDistrictsFor(null).Where(d => d.Name.Equals("Melk")).Single(),
                Incidence = 69.3,
                Infected = 10,
                Recovered = 12,
                Deceased = 13,
                FromUser = test_users[0]
            });
            test_reports.Add(new Report
            {
                Date = DateTime.Now,
                ResponsibleDistrict = dashboard.FindDistrictsFor(null).Where(d => d.Name.Equals("Perg")).Single(),
                Incidence = 5.1,
                Infected = 1,
                Recovered = 2,
                Deceased = 3,
                FromUser = test_users[0]
            });
            test_reports.Add(new Report
            {
                Date = DateTime.Now,
                ResponsibleDistrict = dashboard.FindDistrictsFor(null).Where(d => d.Name.Equals("Perg")).Single(),
                Incidence = 100.5,
                Infected = 9000,
                Recovered = 2,
                Deceased = 3,
                FromUser = test_users[0]
            });

            // makes sure that the report operations work
            test_reports[1] = dashboard.AddReport(test_reports[1]);
            test_reports[2] = dashboard.AddReport(test_reports[2]);
            test_reports[3].Id = test_reports[2].Id;



        }

        [TestMethod]
        public void TestLogin()
        {
            // given
            User u = test_users[0];

            // when

            // then
            // check if a user with that name and (hashed) password exists
            Assert.AreEqual(dashboard.Login(u.Name, u.Password), true);
        }

        [TestMethod]
        public void TestAddUser()
        {
            // given
            User u = test_users[1];

            // when
            bool before = dashboard.Login(u.Name, u.Password);
            dashboard.AddUser(u.Name, u.Password);
            bool after = dashboard.Login(u.Name, u.Password);

            // then
            // check if the user has not been in the DB before, but is, after the insert
            Assert.AreEqual(before, false);
            Assert.AreEqual(after, true);
        }

        [TestMethod]
        public void TestRemoveUser()
        {
            // given
            User u = test_users[2];

            // when
            bool before = dashboard.Login(u.Name, u.Password);
            dashboard.RemoveUser(u.Name, u.Password);
            bool after = dashboard.Login(u.Name, u.Password);

            // then
            // check if the user has been in the DB before, but isnt after the removal
            Assert.AreEqual(before, true);
            Assert.AreEqual(after, false);
        }

        [TestMethod]
        public void TestUpdateUser()
        {
            // given
            User u_old = test_users[3];
            User u_new = test_users[4];

            // when
            bool before_old = dashboard.Login(u_old.Name, u_old.Password);
            bool before_new = dashboard.Login(u_new.Name, u_new.Password);
            dashboard.UpdateUser(u_new, u_old.Name, u_old.Password);
            bool after_old = dashboard.Login(u_old.Name, u_old.Password);
            bool after_new = dashboard.Login(u_new.Name, u_new.Password);

            // then
            // check if the user was in the list before and disappears (because user name has changed)
            // also verify that the updated user hasnt been in the list before, but now is
            Assert.AreEqual(true, before_old);
            Assert.AreEqual(false, before_new);
            Assert.AreEqual(false, after_old);
            Assert.AreEqual(true, after_new);
        }

        [TestMethod]
        public void TestStates()
        {
            // given
            IList<State> states = dashboard.States;
            IList<State> reference = new List<State>();
            reference.Add(new State { Name = "Burgenland" });
            reference.Add(new State { Name = "Kärnten" });
            reference.Add(new State { Name = "Oberösterreich" });
            reference.Add(new State { Name = "Niederösterreich" });
            reference.Add(new State { Name = "Steiermark" });
            reference.Add(new State { Name = "Salzburg" });
            reference.Add(new State { Name = "Tirol" });
            reference.Add(new State { Name = "Vorarlberg" });
            reference.Add(new State { Name = "Wien" });

            // when

            // then
            // there are only 9 states, and the above defined ones should be inside the list
            Assert.AreEqual(9, states.Count);
            foreach(State ref_state in reference)
            {
                Assert.AreEqual(true, states.Contains(ref_state));
            }
        }

        [TestMethod]
        public void TestDistricts()
        {
            // given
            IList<District> districts = dashboard.FindDistrictsFor(null);
            IList<District> filteredDistricts = dashboard.FindDistrictsFor("Oberösterreich");
            // when

            // then
            // it is stated that only 79 districts should exist, however that is the amount of POLITICAL districts.
            // 94 is the correct number
            Assert.AreEqual(94, districts.Count);
            Assert.AreEqual(true, districts.Count > filteredDistricts.Count);
        }

        [TestMethod]
        public void TestKnownState()
        {
            // given
            string stateName = "Oberösterreich";

            // when

            // then
            Assert.AreEqual(true, dashboard.IsKnownState(stateName));
        }

        [TestMethod]
        public void TestKnownDistrict()
        {
            // given
            string districtName = "Freistadt";

            // when

            // then
            Assert.AreEqual(true, dashboard.IsKnownDistrict(districtName));
        }

        [TestMethod]
        public void TestGetAllReports()
        {
            IList<Report> reports = dashboard.GetAllReports();

            // List shouldnt be empty
            Assert.AreEqual(true, reports.Count > 0);
        }
        
        [TestMethod]
        public void TestGetAllReportsTimeWindow()
        {
            DateTime from = DateTime.Parse("14.10.2020");
            DateTime to = DateTime.Parse("24.12.2020");
            IList<Report> reports = dashboard.GetAllReports(from, to);

            // The list should contain entries (not empty) and also each entry should be in the timewindow
            Assert.AreEqual(true, reports.Count > 0);
            foreach (Report r in reports)
            {
                Assert.AreEqual(true, r.Date >= from && r.Date <= to);
            }
        }

        [TestMethod]
        public void TestGetReportsForState()
        {
            IList<Report> reports = dashboard.GetReportsForState("Oberösterreich");

            // The list should contain entries (not empty) and also each entry should be for the given state
            Assert.AreEqual(true, reports.Count > 0);
            foreach(Report r in reports)
            {
                Assert.AreEqual(true, r.ResponsibleDistrict.ResponsibleState.Name.Equals("Oberösterreich"));
            }
        }

        [TestMethod]
        public void TestGetReportsForStateTimewindow()
        {
            DateTime from = DateTime.Parse("14.10.2020");
            DateTime to = DateTime.Parse("24.12.2020");
            IList<Report> reports = dashboard.GetReportsForState("Oberösterreich", from, to);

            // The list should contain entries (not empty) and also each entry should be in the timewindow and for the given state
            Assert.AreEqual(true, reports.Count > 0);
            foreach (Report r in reports)
            {
                Assert.AreEqual(true, r.ResponsibleDistrict.ResponsibleState.Name.Equals("Oberösterreich"));
                Assert.AreEqual(true, r.Date >= from && r.Date <= to);
            }
        }

        [TestMethod]
        public void TestGetReportsForDistrict()
        {
            IList<Report> reports = dashboard.GetReportsForDistrict("Freistadt");

            // The list should contain entries (not empty) and also each entry should be for the given district
            Assert.AreEqual(true, reports.Count > 0);
            foreach(Report r in reports)
            {
                Assert.AreEqual(true, r.ResponsibleDistrict.Name.Equals("Freistadt"));
            }
        }

        [TestMethod]
        public void TestGetReportsForDistrictTimeWindow()
        {
            DateTime from = DateTime.Parse("14.10.2020");
            DateTime to = DateTime.Parse("24.12.2020");
            IList<Report> reports = dashboard.GetReportsForDistrict("Freistadt", from, to);

            // The list should contain entries (not empty) and also each entry should be in the timewindow and for the given district
            Assert.AreEqual(true, reports.Count > 0);
            foreach (Report r in reports)
            {
                Assert.AreEqual(true, r.ResponsibleDistrict.Name.Equals("Freistadt"));
                Assert.AreEqual(true, r.Date >= from && r.Date <= to);
            }
        }

        [TestMethod]
        public void TestAddReport()
        {
            Report r = test_reports[0];

            // returns the same report with filled Id
            IList<Report> reportsBefore = dashboard.GetReportsForDistrict(r.ResponsibleDistrict.Name);
            Report insertedReport = dashboard.AddReport(r);
            IList<Report> reportsAfter = dashboard.GetReportsForDistrict(r.ResponsibleDistrict.Name);

            // check if the amount of reports has increased by one, and that it couldnt be found before inserting, but after
            Assert.AreEqual(true, insertedReport != null);
            Assert.AreEqual(true, (reportsBefore.Count + 1) == reportsAfter.Count);
            Assert.AreEqual(false, reportsBefore.Contains(insertedReport));
            Assert.AreEqual(true, reportsAfter.Contains(insertedReport));
        }

        [TestMethod]
        public void TestRemoveReport()
        {
            Report r = test_reports[1];

            // returns the same report with filled Id
            IList<Report> reportsBefore = dashboard.GetReportsForDistrict(r.ResponsibleDistrict.Name);
            dashboard.RemoveReport(r);
            IList<Report> reportsAfter = dashboard.GetReportsForDistrict(r.ResponsibleDistrict.Name);

            // check if the amount of reports has decreased by one, and that it could be found before removing, but not after
            Assert.AreEqual(true, (reportsBefore.Count - 1) == reportsAfter.Count);
            Assert.AreEqual(true, reportsBefore.Contains(r));
            Assert.AreEqual(false, reportsAfter.Contains(r));
        }

        [TestMethod]
        public void TestUpdateReport()
        {
            Report r = test_reports[2];
            Report r_updated = test_reports[3];

            // returns the same report with filled Id
            IList<Report> reportsBefore = dashboard.GetReportsForDistrict(r.ResponsibleDistrict.Name);
            dashboard.UpdateReport(r_updated);
            IList<Report> reportsAfter = dashboard.GetReportsForDistrict(r.ResponsibleDistrict.Name);

            Report reportBefore = reportsBefore.Where(re => re.Id.Equals(r.Id)).Single();
            Report reportAfter = reportsAfter.Where(re => re.Id.Equals(r.Id)).Single();

            // check if the amount of reports has stayed the same, and that the occurences have swapped
            Assert.AreEqual(true, reportsBefore.Count == reportsAfter.Count);
            // true, because the key stays the same
            Assert.AreEqual(true, reportsBefore.Contains(r));
            Assert.AreEqual(true, reportsAfter.Contains(r_updated));
            // but the incidence should have changed
            Assert.AreEqual(true, reportBefore.Incidence != reportAfter.Incidence);
        }

        [TestCleanup]
        public void Cleanup()
        {
            // make sure that none of the new or updated entries for testing purposes remain in the DB
            dashboard.RemoveUser(test_users[2].Name, test_users[2].Password);
            dashboard.RemoveUser(test_users[3].Name, test_users[3].Password);
            dashboard.RemoveUser(test_users[4].Name, test_users[4].Password);

            dashboard.RemoveReport(test_reports[1]);
            dashboard.RemoveReport(test_reports[3]);
        }
    }
}
