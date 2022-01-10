using Microsoft.AspNetCore.Mvc;
using SWO5.Currency.Logic;
using SWO5.Currency.Domain;

namespace SWO5.Currency.Web.Controllers
{
    public class CurrencyController : Controller
    {
        private readonly IManager<CurrencyType> manager = CurrencyConverterFactory.CreateCurrencyTypeManager();

        public IActionResult Index()
        {
            return View(manager.FindAll()); // as convention returns View with name of this controller without suffix
        }

        // GET
        public IActionResult Edit(int id)
        {
            CurrencyType currencyType = manager.FindById(id);
            return View(currencyType);
        }

        [HttpPost]
        public IActionResult Edit(CurrencyType currencyType)
        {
            if(ModelState.IsValid)
            {
                manager.Update(currencyType);
                return RedirectToAction("Index");
            } else
            {
                return View(currencyType);
            }
        }
    }
}
