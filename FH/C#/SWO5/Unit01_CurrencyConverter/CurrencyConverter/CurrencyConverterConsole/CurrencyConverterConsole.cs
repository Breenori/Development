using System;
using SWO5.Currency.Logic;
// to add this include, rightclick project and add project reference 

namespace SWO5.Currency.App
{
    class CurrencyConverterConsole
    {
        private ICurrencyConverter currencyConverter = CurrencyConverterFactory.CreateCurrencyConverter();

        // geht nicht wegen scope! --> kein scope = nur im eigenen assembly
        //private ICurrencyConverter currencyConverter = new SimpleCurrencyConverter();

        static void Main(string[] args)
        {
            Console.WriteLine("Hello World!");
        }
    }
}
