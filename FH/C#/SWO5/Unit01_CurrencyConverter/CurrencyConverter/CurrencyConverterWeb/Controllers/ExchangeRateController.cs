using Microsoft.AspNetCore.Mvc;
using SWO5.Currency.Logic;
using SWO5.Currency.Domain;
using SWO5.Currency.Web.Models;
using Microsoft.AspNetCore.Mvc.Rendering;
using System.Collections.Generic;

namespace SWO5.Currency.Web.Controllers
{
    public class ExchangeRateController : Controller
    {
        private IManager<CurrencyType> currencyTypeManager = CurrencyConverterFactory.CreateCurrencyTypeManager();
        private IManager<ExchangeRate> exchangeRateManager = CurrencyConverterFactory.CreateExchangeRateManager(); 

        public IActionResult Create()
        {
            ExchangeRateViewModel viewModel = new ExchangeRateViewModel();
            viewModel.ExchangeRate = new ExchangeRate();
            viewModel.AvailableCurrencyTypes = new List<SelectListItem>();
            var currencies = currencyTypeManager.FindAll();

            foreach(var currency in currencies)
            {
                viewModel.AvailableCurrencyTypes.Add(new SelectListItem { Value = currency.Id.ToString(), Text=currency.Code }); ;
            }

            return View(viewModel);
        }

        [HttpPost]
        public IActionResult Create(ExchangeRateViewModel viewModel)
        {
            if(ModelState.IsValid)
            {
                CurrencyType currencyType = currencyTypeManager.FindById(viewModel.SelectedCurrencyTypeId);
                ExchangeRate rate = viewModel.ExchangeRate;
                rate.CurrencyType = currencyType;
                exchangeRateManager.Create(rate);
                return RedirectToAction("Index", "Currency");
            }
            return RedirectToAction("Create");
        }

    }
}
