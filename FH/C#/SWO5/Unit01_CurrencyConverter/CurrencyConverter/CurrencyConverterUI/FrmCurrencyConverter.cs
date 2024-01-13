using SWO5.Currency.Logic;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace SWO5.Currency.UI
{
    public partial class FrmCurrencyConverter : Form
    {
        const string EUR_CODE = "EUR";
        private ICurrencyConverter converter = CurrencyConverterFactory.CreateCurrencyConverter();

        public FrmCurrencyConverter()
        {
            InitializeComponent();
            this.cmbCurrency.Items.AddRange(converter.Currencies);
            this.cmbCurrency.SelectedIndex = 0;
        }

        private void numRate_ValueChanged(object sender, EventArgs e)
        {
            Convert(this.cmbCurrency.SelectedItem as string, Decimal.ToDouble(this.numRate.Value));
        }

        private void Convert(string code, double value)
        {
            this.txtResult.Text = converter.ConvertFromTo(EUR_CODE, code, value).ToString("0.00");
        }

        private void cmbCurrency_SelectedIndexChanged(object sender, EventArgs e)
        {
            Convert(this.cmbCurrency.SelectedItem as string, Decimal.ToDouble(this.numRate.Value));
        }
    }
}
