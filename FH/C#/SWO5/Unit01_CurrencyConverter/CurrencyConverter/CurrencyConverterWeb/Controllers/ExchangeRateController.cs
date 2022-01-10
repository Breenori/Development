using Microsoft.AspNetCore.Mvc;

namespace SWO5.Currency.Web.Controllers
{
    public class ExchangeRateController : Controller
    {
        public IActionResult Create()
        {
            return View();
        }
    }
}
