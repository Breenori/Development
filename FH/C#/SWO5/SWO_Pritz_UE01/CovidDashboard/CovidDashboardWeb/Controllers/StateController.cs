using Microsoft.AspNetCore.Mvc;
using SWO5.Dashboard.Domain;
using SWO5.Dashboard.Logic;
using System.Collections.Generic;
using System.Linq;

namespace SWO5.Dashboard.Web.Controllers
{
    public class StateController : Controller
    {
        private IManager<State> stateManager = CovidDashboardFactory.CreateStateManager();
        private IManager<District> districtManager = CovidDashboardFactory.CreateDistrictManager();

        public IActionResult Index()
        {
            return View(stateManager.FindAll());
        }
        public IActionResult Create()
        {
            return View(new State());
        }

        [HttpPost]
        public IActionResult Create(State state)
        {
            if (ModelState.IsValid)
            {
                stateManager.Create(state);
                return RedirectToAction("Index", "State");
            }
            return View("Create");
        }

        public IActionResult Edit(int id)
        {
            State state = stateManager.FindById(id);
            return View(state);
        }

        [HttpPost]
        public IActionResult Edit(State state)
        {
            if (ModelState.IsValid)
            {
                stateManager.Update(state);
                return RedirectToAction("Index");
            }
            else
            {
                return View(state);
            }
        }

        public IActionResult Delete(int id)
        {
            State state = stateManager.FindById(id);
            return View(state);
        }

        [HttpPost]
        public IActionResult Delete(State state)
        {
            List<District> districts = districtManager.FindAll().Where(r => r.ResponsibleState.Id == state.Id).ToList();
            if (districts.Count() > 0)
            {
                ModelState.AddModelError("error", $"The state '{state.Name}' cannot be deleted since it is being referenced in one or more districts.");
            }

            if (ModelState.IsValid)
            {
                stateManager.Delete(state);
                return RedirectToAction("Index");
            }
            else
            {
                return View(state);
            }
        }
    }
}
