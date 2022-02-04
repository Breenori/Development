using Microsoft.AspNetCore.Http;
using Microsoft.AspNetCore.Mvc;
using SWO5.Currency.API.Services;
using SWO5.Currency.Domain;
using System.Collections.Generic;

namespace SWO5.Currency.API.Controllers
{
    [Route("api/[controller]")]
    [Produces("application/json")]
    [ApiController]
    public class CurrencyController : ControllerBase
    {
        private readonly CurrencyConverterLogicAdapter adapter;

        public CurrencyController(CurrencyConverterLogicAdapter adapter)
        {
            this.adapter = adapter;
        }

        [HttpGet]
        public ActionResult<IList<CurrencyType>> GetCurrencies()
        {
            return Ok(adapter.CurrencyTypeManager.FindAll());
        }
    }
}
