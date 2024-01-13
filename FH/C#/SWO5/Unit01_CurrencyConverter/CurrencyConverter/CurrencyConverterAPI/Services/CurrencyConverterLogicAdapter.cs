using SWO5.Currency.Domain;
using SWO5.Currency.Logic;

namespace SWO5.Currency.API.Services
{
    public class CurrencyConverterLogicAdapter
    {
        private readonly IManager<CurrencyType> currencyTypeManager = CurrencyConverterFactory.CreateCurrencyTypeManager();

        public IManager<CurrencyType> CurrencyTypeManager
        {
            get { return currencyTypeManager; }
        }
    }
}
