using System;
using System.Linq;
using System.Reflection;

namespace SWO5.Currency.DAL
{
    public class DaoFactoryProvider
    {
        private static IDaoFactory daoFactory; 
        private const string ASSEMBLY_PATH = @"C:\public\currencyconverter\CurrencyConverterDALSQLe.dll";

        private static void InitializeFactory()
        {
            Assembly asm = Assembly.LoadFrom(ASSEMBLY_PATH);
            var factories = asm.GetTypes()
                                .Where( type => type.GetCustomAttribute(typeof(DaoFactoryCandidate)) != null );
            if( !factories.Any() )
            {
                throw new ArgumentException("No valid DaoFactory found!");
            } 
            if( factories.Count() > 1 )
            {
                throw new ArgumentException("Multiple Factories found!");
            }

            Type factory = factories.Single();
            DaoFactoryCandidate candidateAttr = (DaoFactoryCandidate) factory.GetCustomAttribute(typeof(DaoFactoryCandidate));
            daoFactory = (IDaoFactory) Activator.CreateInstance(factory);
            Console.WriteLine( $"Using database factory for provider {candidateAttr.ProviderName}" );
        }

        public static IDaoFactory GetDaoFactory()
        {
            if (daoFactory == null)
            {
                InitializeFactory();
            }
            return daoFactory;
        }


    }
}
