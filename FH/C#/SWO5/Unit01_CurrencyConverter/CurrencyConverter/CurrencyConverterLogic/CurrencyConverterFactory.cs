
namespace SWO5.Currency.Logic
{
    public class CurrencyConverterFactory
    {

        public static ICurrencyConverter CreateCurrencyConverter()
        {
            // Version 1: very basic implementation of BL
            // return new SimpleCurrencyConverter();
            // Version 2: xml-based currency converter
            // return new XmlBasedCurrencyConverter();
            // Version 3: ado.net based currency converter
            return new SQLeBasedCurrencyConverter();
        }


    }
}
