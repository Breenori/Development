using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using SWO5.Dashboard.Logic;
using SWO5.Dashboard.Domain;
using System.Collections.ObjectModel;
using LiveCharts;
using LiveCharts.Wpf;
using System.Windows.Media;
using System.Windows;
using System.Windows.Input;
using Microsoft.Win32;
using System.IO;

namespace SWO5.Dashboard.WPF
{
    public class CovidModel : INotifyPropertyChanged
    {
        // Since the data isn't being updated daily, some buttons might not be testable at later dates
        // --> Sets the "current Date" to the last date inside the dataset
        // e.g. if 7 days pass without adding data, showing data for "last week" still works!
        private bool testMode = true;
        public DateTime currentDate
        {
            get { 
                if (testMode && Reports.Count() > 0)
                {
                    DateTime lastInReports = Reports.OrderBy(r => r.Date).Select(r => r.Date).Last();
                    lastInReports.AddSeconds(-lastInReports.Second);
                    lastInReports.AddMinutes(-lastInReports.Minute);
                    lastInReports.AddHours(-lastInReports.Hour);
                    return lastInReports;
                } else
                {
                    DateTime today = DateTime.Now;
                    today.AddSeconds(59 - to.Second);
                    today.AddMinutes(59 - to.Minute);
                    today.AddHours(23 - to.Hour);
                    return today;
                }
            }
        }

        // Business Logic
        private ICovidDashboard dashboard = CovidDashboardFactory.CreateCovidDashboard();

        // if no State/District is set = Placeholder
        private State noneState;
        private District noneDistrict;

        #region Properties
        private State state;
        private District district;
        private string chartLegend;

        private string mode;
        private DateTime from;
        private DateTime to;

        private string type;

        public State selectedState
        {
            get { return state; }
            set
            {
                if (value != null)
                {
                    state = value;
                    OnPropertyChanged(nameof(selectedState));

                    if (selectedState != noneState)
                    {
                        Districts = new ObservableCollection<District>(dashboard.FindDistrictsFor(state.Name));
                    }
                    else
                    {
                        Districts = new ObservableCollection<District>();
                    }
                    if (state != noneState)
                    {
                        chartLegend = state.Name;
                    }
                    else
                    {
                        chartLegend = "Gesamt";
                    }
                    Districts.Insert(0, noneDistrict);
                    selectedDistrict = noneDistrict;
                    OnPropertyChanged(nameof(selectedDistrict));
                    OnPropertyChanged(nameof(Districts));
                }
            }
        }
        public District selectedDistrict
        {
            get { return district; }
            set
            {
                if (value != null)
                {
                    district = value;
                    OnPropertyChanged(nameof(selectedDistrict));
                    if (district != noneDistrict)
                    {
                        chartLegend = value.Name;
                    } else if(state != noneState) {
                        chartLegend = state.Name;
                    } else
                    {
                        chartLegend = "Gesamt";
                    }
                    UpdateChartAsync();
                }
            }
        }
        public string selectedMode
        {
            get { return mode; }
            set
            {
                mode = value;
                OnPropertyChanged(nameof(selectedMode));

                // Get Current Date and set time to 23:59:59
                DateTime today = currentDate;
                if (mode == "Jahr")
                {
                    selectedTimeTo = today;
                    selectedTimeFrom = today.AddYears(-1).AddSeconds(1);
                }
                else if (mode == "Monat")
                {
                    selectedTimeTo = today;
                    selectedTimeFrom = today.AddMonths(-1).AddSeconds(1);
                }
                else if (mode == "Woche")
                {
                    selectedTimeTo = today;
                    selectedTimeFrom = today.AddDays(-7).AddSeconds(1);
                } 

                if(mode == "Auswahl")
                {
                    isTimePickEnabled = true;
                } else
                {
                    isTimePickEnabled = false;
                }
                OnPropertyChanged(nameof(isTimePickEnabled));
                OnPropertyChanged(nameof(selectedTimeTo));
                OnPropertyChanged(nameof(selectedTimeFrom));
                if (mode != "Auswahl")
                {
                    UpdateChartAsync();
                }
            }
        }
        public string selectedType
        {
            get { return type; }
            set
            {
                type = value;
                OnPropertyChanged(nameof(selectedType));
                UpdateChartAsync();
            }
        }
        public DateTime selectedTimeFrom
        {
            get { return from; }
            set
            {
                from = value;
                OnPropertyChanged(nameof(selectedTimeFrom));
                if (isTimePickEnabled)
                {
                    UpdateChartAsync();
                }
            }
        }
        public DateTime selectedTimeTo
        {
            get { return to; }
            set
            {
                to = value;
                OnPropertyChanged(nameof(selectedTimeTo));
                if (isTimePickEnabled)
                {
                    UpdateChartAsync();
                }
            }
        }
        public bool isTimePickEnabled { get; set; }

        public ObservableCollection<Report> Reports { get; set; }
        public ObservableCollection<State> States { get; set; }
        public ObservableCollection<District> Districts { get; set; }
        public ObservableCollection<string> Modes { get; set; }
        public ObservableCollection<string> Types { get; set; }

        public long newCases { get; set; }
        public long activeCases { get; set; }
        public ObservableCollection<Report> stateIncidences { get; set; }

        public event PropertyChangedEventHandler? PropertyChanged;
        public void OnPropertyChanged(string propertyName)
        {
            PropertyChanged?.Invoke(this, new PropertyChangedEventArgs(propertyName));
        }
        #endregion

        #region Commands
        private ICommand exportCommand;
        public ICommand ExportCommand
        {
            get { return exportCommand; }
            set { exportCommand = value; }
        }

        public class ExportCommandHandler : ICommand
        {
            ObservableCollection<Report> exportableReports;
            public event EventHandler? CanExecuteChanged;

            public ExportCommandHandler(ObservableCollection<Report> reports)
            {
                this.exportableReports = reports;   
            }

            public bool CanExecute(object? parameter)
            {
                return true;
            }

            public void Execute(object? parameter)
            {
                SaveFileDialog saveFileDialog = new SaveFileDialog();
                saveFileDialog.Filter = "CSV file (*.csv)|*.csv| All Files (*.*)|*.*";
                saveFileDialog.FilterIndex = 0;
                saveFileDialog.RestoreDirectory = true;

                if(saveFileDialog.ShowDialog() == true)
                {
                    Stream outStream;
                    if((outStream = saveFileDialog.OpenFile()) != null)
                    {
                        StreamWriter streamWriter = new StreamWriter(outStream);
                        foreach(Report report in exportableReports)
                        {
                            streamWriter.WriteLine(report.ToCsv());
                            streamWriter.Flush();
                        }
                        streamWriter.Close();
                        outStream.Close();
                    }
                }
            }
        }
        #endregion

        #region Chart and Data-Acquisition
        private Task<List<Report>> CasesForTask()
        {
            return Task.Factory.StartNew(() => getReports());
        }

        private List<Report> getReports()
        {
            // If both state and district are selected, get data for district in timeframe
            if (state != noneState && district != noneDistrict)
            {
                return dashboard.GetReportsForDistrict(selectedDistrict.Name)
                        .Where(r => r.Date >= from && r.Date <= to).ToList();
            } 
            // if state is selected, but district isn't, group the data and display data on a state basis
            else if (state != noneState && district == noneDistrict)
            {
                return dashboard.GetReportsForState(selectedState.Name)
                        .Where(r => r.Date >= from && r.Date <= to)
                        .GroupBy(r => new { r.Date, r.ResponsibleDistrict.ResponsibleState})
                        .Select(r => new Report
                        {
                            Id = -1,
                            Date = r.Key.Date,
                            ResponsibleDistrict = new District() { Id=-1, Name="-", Population=r.Sum(x => x.ResponsibleDistrict.Population), ResponsibleState=r.Key.ResponsibleState},
                            Incidence = r.Average(x => x.Incidence),
                            Infected = r.Sum(x => x.Infected),
                            Recovered = r.Sum(x => x.Recovered),
                            Deceased = r.Sum(x => x.Deceased)
                        }).ToList();
            }
            // if state AND district are not selected, group data and display on basis of the entire country
            else
            {
                return dashboard.GetAllReports()
                        .Where(r => r.Date >= from && r.Date <= to)
                        .GroupBy(r => r.Date)
                        .Select(r => new Report
                        {
                            Id = -1,
                            Date = r.Key.Date,
                            ResponsibleDistrict = noneDistrict,
                            Incidence = r.Average(x => x.Incidence),
                            Infected = r.Sum(x => x.Infected),
                            Recovered = r.Sum(x => x.Recovered),
                            Deceased = r.Sum(x => x.Deceased)
                        }).ToList();
            }
        }

        private async void UpdateChartAsync()
        {
            series = new SeriesCollection();
            // query Reports
            Reports = new ObservableCollection<Report>(CasesForTask().Result);
            OnPropertyChanged(nameof(Reports));

            if (Reports != null && Reports.Count > 0)
            {
                ExportCommand = new ExportCommandHandler(Reports);
                OnPropertyChanged(nameof(ExportCommand));

                // get data for the different curves
                long[] ys_infected = (from r in Reports
                               select r.Infected).ToArray();
                long[] ys_recovered = (from r in Reports
                                      select r.Recovered).ToArray();
                long[] ys_deceased = (from r in Reports
                                      select r.Deceased).ToArray();
                long[] ys_incidence = (from r in Reports
                                       select (long)r.Incidence).ToArray();

                // get dates for x axis
                string[] xs = (from r in Reports
                               select r.Date.ToShortDateString()).ToArray();

                if (type == "-" || type == "Infiziert")
                {
                    series.Add(
                        new LineSeries
                        {
                            Title = $"Infiziert - {chartLegend}",
                            Values = new ChartValues<long>(ys_infected),
                            StrokeThickness = 1,
                            PointGeometry = null
                        }
                    );
                }
                if (type == "-" || type == "Genesen")
                {
                    series.Add(
                    new LineSeries
                    {
                        Title = $"Genesen - {chartLegend}",
                        Values = new ChartValues<long>(ys_recovered),
                        StrokeThickness = 1,
                        PointGeometry = null,
                        Stroke = Brushes.Green,
                        Fill = Brushes.PaleGreen
                    }
                    );
                }
                if (type == "-" || type == "Verstorben")
                {
                    series.Add(
                    new LineSeries
                    {
                        Title = $"Verstorben - {chartLegend}",
                        Values = new ChartValues<long>(ys_deceased),
                        StrokeThickness = 1,
                        PointGeometry = null,
                        Stroke = Brushes.Black,
                        Fill = Brushes.LightGray
                    }
                    );
                }
                if (type == "-" || type == "Inzidenz")
                {
                    series.Add(
                    new LineSeries
                    {
                        Title = $"Inzidenz - {chartLegend}",
                        Values = new ChartValues<long>(ys_incidence),
                        StrokeThickness = 2,
                        PointGeometry = null,
                        Stroke = Brushes.LightSalmon,
                        Fill = Brushes.Transparent
                    }
                    );
                }


                Labels = xs;
            } else
            {
                // If no data was found, but initialization has already passed, show a warning
                if (state != null && district != null && mode != null)
                {
                    MessageBox.Show("Für den angegebenen Zeitraum und Ort konnten keine Daten gefunden werden.", "Hinweis");
                }
            }
            OnPropertyChanged(nameof(Series));
            OnPropertyChanged(nameof(Labels));
        }
        #endregion

        #region Series
        private readonly object yFormatterLock = new object();
        private readonly object seriesLock = new object();
        private readonly object labelsLock = new object();
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

        #endregion

        #region Constructor and Initialize
        public CovidModel()
        {
            Initialize();
        }

        private void Initialize()
        {
            noneState = new State() { Id = -1, Name = "-" };
            States = new ObservableCollection<State>(dashboard.States);
            States.Insert(0,noneState);
            selectedState = States[0];

            noneDistrict = new District() { Id = -1, Name = "-", ResponsibleState=noneState, Population=0 };
            Districts = new ObservableCollection<District>();
            Districts.Insert(0, noneDistrict);
            selectedDistrict = Districts[0];

            Modes = new ObservableCollection<string>();
            Modes.Add("Jahr");
            Modes.Add("Monat");
            Modes.Add("Woche");
            Modes.Add("Auswahl");
            selectedMode = "Jahr";

            Types = new ObservableCollection<string>();
            Types.Add("-");
            Types.Add("Infiziert");
            Types.Add("Genesen");
            Types.Add("Verstorben");
            Types.Add("Inzidenz");
            selectedType = "-";

            IList<Report> allReports = dashboard.GetAllReports();
            newCases = allReports != null ? allReports
                .Where(r => r.Date == currentDate)
                .Sum(r => r.Infected) 
                : 0;
            OnPropertyChanged(nameof(newCases));
            activeCases = allReports != null ? allReports
                .Sum(r => r.Infected) - Reports.Sum(r => r.Recovered) - Reports.Sum(r => r.Deceased) 
                : 0;
            OnPropertyChanged(nameof(activeCases));
            stateIncidences = allReports != null ? new ObservableCollection<Report>(allReports
                .Where(r => r.Date == currentDate)
                .GroupBy(r => new { r.ResponsibleDistrict.ResponsibleState })
                .Select(r => new Report {
                    Incidence=r.Average(r => r.Incidence),
                    ResponsibleDistrict = new District() { Id=-1, Name="-", Population=0, ResponsibleState = r.Key.ResponsibleState }
                }).ToList()) : new ObservableCollection<Report>();
            OnPropertyChanged(nameof(stateIncidences));

            UpdateChartAsync();
        }
        #endregion
    }
}
