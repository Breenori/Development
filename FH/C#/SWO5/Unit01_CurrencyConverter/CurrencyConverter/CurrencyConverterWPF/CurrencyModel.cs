using SWO5.Currency.Logic;
using System;
using System.ComponentModel;
using System.Linq;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using SWO5.Currency.Domain;
using LiveCharts;
using LiveCharts.Wpf;
using System.Threading;
using System.Windows;
using System.Threading.Tasks;

namespace SWO5.Currency.WPF
{
    public class CurrencyModel : INotifyPropertyChanged
    {
        #region Properties
        public event PropertyChangedEventHandler PropertyChanged;
        private ICurrencyConverter converter = CurrencyConverterFactory.CreateCurrencyConverter();

        private CurrencyType currencyType;
        private double amount;

        public CurrencyType SelectedCurrency
        {
            get { return currencyType; }
            set { 
                currencyType = value;
                OnPropertyChanged(nameof(SelectedCurrency));
                OnPropertyChanged(nameof(Result));
                OnPropertyChanged(nameof(MapData));
                // Version 1: loading data from UI thread - UI is blocked
                //UpdateChart();
                // Version 2: loading data in background via thread
                //UpdateChartViaThread();
                // Version 3: Create Task
                ///UpdateChartViaTask();
                // Version 4: async/await combination
                UpdateChartAsync();
            }
        }

        public double Amount
        {
            get { return amount; }
            set { 
                amount = value;
                OnPropertyChanged(nameof(Amount));
                OnPropertyChanged(nameof(Result));
            }
        }

        public ObservableCollection<CurrencyType> Currencies
        {
            get;
            set;
        }

        public double Result
        {
            get { return converter.ConvertFromTo("EUR", SelectedCurrency.Code, Amount); }
        }

        public void OnPropertyChanged(string propertyName)
        {
            PropertyChanged?.Invoke(this, new PropertyChangedEventArgs(propertyName));
        }

        private readonly object yFormatterLock = new object();
        private readonly object seriesLock = new object();
        private readonly object labelsLock = new object();
        #endregion

        #region Livechart
        public Dictionary<string, double> MapData { 
            get { return UpdateMap(); }
            
        }

        private Dictionary<string, double> UpdateMap()
        {
            Dictionary<string, double> values = new Dictionary<string, double>();
            IList<Country> countries = converter.FindCountriesFor(this.SelectedCurrency);
            if(countries != null && countries.Count > 0)
            {
                foreach(Country country in countries)
                {
                    values[country.Code] = 100;
                }
            }

            return values;
        }
        
        private void UpdateChartViaThread()
        {
            new Thread(UpdateChart).Start();
        }

        private void UpdateChartViaTask()
        {
            Task.Factory.StartNew (() => UpdateChart());
        }


        private Task<IList<Tuple<DateTime, ExchangeRate>>> RatesForTask()
        {
            return Task.Factory.StartNew(() => converter.FindExchangeRatesFor(SelectedCurrency.Code));
        }
        private async void UpdateChartAsync()
        {
            series = new SeriesCollection();
            IList<Tuple<DateTime, ExchangeRate>> rates = RatesForTask().Result;//converter.FindExchangeRatesFor(SelectedCurrency.Code);
            if (rates != null && rates.Count > 0)
            {
                double[] ys = (from r in rates
                               select r.Item2.Rate).ToArray();
                string[] xs = (from r in rates
                               select r.Item1.ToShortDateString()).ToArray();

                // always do this in the UI thread
                //Application.Current.Dispatcher.Invoke(new Action(() => {
                    series.Add(
                        new LineSeries
                        {
                            Title = $"{SelectedCurrency.Code}",
                            Values = new ChartValues<double>(ys),
                            StrokeThickness = 1,
                            PointGeometry = null
                        }
                    );
                    Labels = xs;
                    YFormatter = value => value.ToString("F2");
                    OnPropertyChanged(nameof(Series));
                    OnPropertyChanged(nameof(Labels));
                    OnPropertyChanged(nameof(YFormatter));
                //}));
            }
        }

        private void UpdateChart()
        {
            series = new SeriesCollection();
            IList<Tuple<DateTime, ExchangeRate>> rates = converter.FindExchangeRatesFor(SelectedCurrency.Code);
            if(rates != null && rates.Count > 0)
            {
                double[] ys = (from r in rates
                               select r.Item2.Rate).ToArray();
                string[] xs = (from r in rates
                               select r.Item1.ToShortDateString()).ToArray();

                // always do this in the UI thread
                Application.Current.Dispatcher.Invoke(new Action(() => { 
                    series.Add(
                        new LineSeries
                        {
                            Title = $"{SelectedCurrency.Code}",
                            Values = new ChartValues<double>(ys),
                            StrokeThickness = 1,
                            PointGeometry = null
                        }
                    );
                    Labels = xs;
                    YFormatter = value => value.ToString("F2");
                    OnPropertyChanged(nameof(Series));
                    OnPropertyChanged(nameof(Labels));
                    OnPropertyChanged(nameof(YFormatter));
                }));
            }
        }
        #endregion

        public CurrencyModel()
        {
            Initialize();
        }

        private void Initialize()
        {
            Currencies = new ObservableCollection<CurrencyType>(converter.CurrencyTypes);
            if (Currencies != null && Currencies.Count > 0)
            {
                SelectedCurrency = Currencies.First();
            }
            Amount = 0.0;
        }



        private SeriesCollection series;

        public SeriesCollection Series
        {
            get { lock (seriesLock) { return series; } }
            set { lock (seriesLock) { series = value; } }
        }

        private string[] labels;

        public string[] Labels
        {
            get { lock (labelsLock) { return labels; } }
            set { lock (labelsLock) { labels = value; } }
        }

        private Func<double, string> yFormatter;

        public Func<double, string> YFormatter
        {
            get { lock (yFormatterLock) { return yFormatter; } }
            set { lock (yFormatterLock) { yFormatter = value; } }
        }


    }
}
