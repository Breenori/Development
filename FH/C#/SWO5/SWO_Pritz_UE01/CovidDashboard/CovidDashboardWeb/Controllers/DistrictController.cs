using Microsoft.AspNetCore.Mvc;
using Microsoft.AspNetCore.Mvc.Rendering;
using SWO5.Dashboard.Domain;
using SWO5.Dashboard.Logic;
using SWO5.Dashboard.Web.Models;
using System.Collections.Generic;
using System.Linq;

namespace SWO5.Dashboard.Web.Controllers
{
    public class DistrictController : Controller
    {
        private IManager<District> districtManager = CovidDashboardFactory.CreateDistrictManager();
        private IManager<State> stateManager = CovidDashboardFactory.CreateStateManager();
        private IManager<Report> reportManager = CovidDashboardFactory.CreateReportManager();


        public IActionResult Index()
        {
            return View(districtManager.FindAll());
        }
        public IActionResult Create()
        {
            DistrictViewModel dvm = new DistrictViewModel();
            dvm.District = new District();
            dvm.AvailableStates = new List<SelectListItem>();

            var states = stateManager.FindAll();

            foreach (var state in states)
            {
                dvm.AvailableStates.Add(new SelectListItem { Value = state.Id.ToString(), Text = state.Name }); ;
            }

            return View(dvm);
        }

        [HttpPost]
        public IActionResult Create(DistrictViewModel dvm)
        {
            if (ModelState.IsValid)
            {
                State state = stateManager.FindById(dvm.SelectedStateId);
                District district = dvm.District;
                district.ResponsibleState = state;
                districtManager.Create(district);
                return RedirectToAction("Index", "District");
            } else
            {
                dvm.AvailableStates = new List<SelectListItem>();
                var states = stateManager.FindAll();
                foreach (var state in states)
                {
                    dvm.AvailableStates.Add(new SelectListItem { Value = state.Id.ToString(), Text = state.Name }); ;
                }

                return View(dvm);
            }
        }

        public IActionResult Edit(int id)
        {
            DistrictViewModel dvm = new DistrictViewModel();
            dvm.District = districtManager.FindById(id);
            dvm.AvailableStates = new List<SelectListItem>();

            var states = stateManager.FindAll();

            foreach (var state in states)
            {
                dvm.AvailableStates.Add(new SelectListItem { Value = state.Id.ToString(), Text = state.Name }); ;
            }

            dvm.SelectedStateId = dvm.District.ResponsibleState.Id;

            return View(dvm);
        }

        [HttpPost]
        public IActionResult Edit(DistrictViewModel dvm)
        {
            if (ModelState.IsValid)
            {
                State state = stateManager.FindById(dvm.SelectedStateId);
                District district = dvm.District;
                district.ResponsibleState = state;
                districtManager.Update(district);
                return RedirectToAction("Index");
            }
            else
            {
                dvm.AvailableStates = new List<SelectListItem>();
                var states = stateManager.FindAll();
                foreach (var state in states)
                {
                    dvm.AvailableStates.Add(new SelectListItem { Value = state.Id.ToString(), Text = state.Name }); ;
                }

                return View(dvm);
            }
        }

        public IActionResult Delete(int id)
        {
            District district = districtManager.FindById(id);
            return View(district);
        }

        [HttpPost]
        public IActionResult Delete(District district)
        {
            if (reportManager.FindAll().Where(r => r.ResponsibleDistrict.Id == district.Id).Count() > 0)
            {
                ModelState.AddModelError("error", $"The district '{district.Name}' cannot be deleted since it is being referenced in one or more reports.");
            }

            if (ModelState.IsValid)
            {
                districtManager.Delete(district);
                return RedirectToAction("Index");
            }
            else
            {
                return View(district);
            }
        }
    }
}
