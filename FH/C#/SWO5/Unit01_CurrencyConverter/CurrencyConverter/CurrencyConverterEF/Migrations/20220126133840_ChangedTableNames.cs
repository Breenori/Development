using Microsoft.EntityFrameworkCore.Migrations;

namespace SWO5.Currency.EF.Migrations
{
    public partial class ChangedTableNames : Migration
    {
        protected override void Up(MigrationBuilder migrationBuilder)
        {
            migrationBuilder.DropForeignKey(
                name: "FK_Countries_CurrencyTypes_CurrencyTypeId",
                table: "Countries");

            migrationBuilder.DropForeignKey(
                name: "FK_ExchangeRates_CurrencyTypes_CurrencyTypeId",
                table: "ExchangeRates");

            migrationBuilder.DropForeignKey(
                name: "FK_ExchangeRates_Instants_InstantId",
                table: "ExchangeRates");

            migrationBuilder.DropPrimaryKey(
                name: "PK_Instants",
                table: "Instants");

            migrationBuilder.DropPrimaryKey(
                name: "PK_ExchangeRates",
                table: "ExchangeRates");

            migrationBuilder.DropPrimaryKey(
                name: "PK_CurrencyTypes",
                table: "CurrencyTypes");

            migrationBuilder.DropPrimaryKey(
                name: "PK_Countries",
                table: "Countries");

            migrationBuilder.RenameTable(
                name: "Instants",
                newName: "Instant");

            migrationBuilder.RenameTable(
                name: "ExchangeRates",
                newName: "ExchangeRate");

            migrationBuilder.RenameTable(
                name: "CurrencyTypes",
                newName: "CurrencyType");

            migrationBuilder.RenameTable(
                name: "Countries",
                newName: "Country");

            migrationBuilder.RenameColumn(
                name: "InstantId",
                table: "ExchangeRate",
                newName: "instant_id");

            migrationBuilder.RenameColumn(
                name: "CurrencyTypeId",
                table: "ExchangeRate",
                newName: "currency_id");

            migrationBuilder.RenameIndex(
                name: "IX_ExchangeRates_InstantId",
                table: "ExchangeRate",
                newName: "IX_ExchangeRate_instant_id");

            migrationBuilder.RenameIndex(
                name: "IX_ExchangeRates_CurrencyTypeId",
                table: "ExchangeRate",
                newName: "IX_ExchangeRate_currency_id");

            migrationBuilder.RenameColumn(
                name: "CurrencyTypeId",
                table: "Country",
                newName: "currency_id");

            migrationBuilder.RenameIndex(
                name: "IX_Countries_CurrencyTypeId",
                table: "Country",
                newName: "IX_Country_currency_id");

            migrationBuilder.AddPrimaryKey(
                name: "PK_Instant",
                table: "Instant",
                column: "Id");

            migrationBuilder.AddPrimaryKey(
                name: "PK_ExchangeRate",
                table: "ExchangeRate",
                column: "Id");

            migrationBuilder.AddPrimaryKey(
                name: "PK_CurrencyType",
                table: "CurrencyType",
                column: "Id");

            migrationBuilder.AddPrimaryKey(
                name: "PK_Country",
                table: "Country",
                column: "Id");

            migrationBuilder.AddForeignKey(
                name: "FK_Country_CurrencyType_currency_id",
                table: "Country",
                column: "currency_id",
                principalTable: "CurrencyType",
                principalColumn: "Id",
                onDelete: ReferentialAction.Restrict);

            migrationBuilder.AddForeignKey(
                name: "FK_ExchangeRate_CurrencyType_currency_id",
                table: "ExchangeRate",
                column: "currency_id",
                principalTable: "CurrencyType",
                principalColumn: "Id",
                onDelete: ReferentialAction.Restrict);

            migrationBuilder.AddForeignKey(
                name: "FK_ExchangeRate_Instant_instant_id",
                table: "ExchangeRate",
                column: "instant_id",
                principalTable: "Instant",
                principalColumn: "Id",
                onDelete: ReferentialAction.Restrict);
        }

        protected override void Down(MigrationBuilder migrationBuilder)
        {
            migrationBuilder.DropForeignKey(
                name: "FK_Country_CurrencyType_currency_id",
                table: "Country");

            migrationBuilder.DropForeignKey(
                name: "FK_ExchangeRate_CurrencyType_currency_id",
                table: "ExchangeRate");

            migrationBuilder.DropForeignKey(
                name: "FK_ExchangeRate_Instant_instant_id",
                table: "ExchangeRate");

            migrationBuilder.DropPrimaryKey(
                name: "PK_Instant",
                table: "Instant");

            migrationBuilder.DropPrimaryKey(
                name: "PK_ExchangeRate",
                table: "ExchangeRate");

            migrationBuilder.DropPrimaryKey(
                name: "PK_CurrencyType",
                table: "CurrencyType");

            migrationBuilder.DropPrimaryKey(
                name: "PK_Country",
                table: "Country");

            migrationBuilder.RenameTable(
                name: "Instant",
                newName: "Instants");

            migrationBuilder.RenameTable(
                name: "ExchangeRate",
                newName: "ExchangeRates");

            migrationBuilder.RenameTable(
                name: "CurrencyType",
                newName: "CurrencyTypes");

            migrationBuilder.RenameTable(
                name: "Country",
                newName: "Countries");

            migrationBuilder.RenameColumn(
                name: "instant_id",
                table: "ExchangeRates",
                newName: "InstantId");

            migrationBuilder.RenameColumn(
                name: "currency_id",
                table: "ExchangeRates",
                newName: "CurrencyTypeId");

            migrationBuilder.RenameIndex(
                name: "IX_ExchangeRate_instant_id",
                table: "ExchangeRates",
                newName: "IX_ExchangeRates_InstantId");

            migrationBuilder.RenameIndex(
                name: "IX_ExchangeRate_currency_id",
                table: "ExchangeRates",
                newName: "IX_ExchangeRates_CurrencyTypeId");

            migrationBuilder.RenameColumn(
                name: "currency_id",
                table: "Countries",
                newName: "CurrencyTypeId");

            migrationBuilder.RenameIndex(
                name: "IX_Country_currency_id",
                table: "Countries",
                newName: "IX_Countries_CurrencyTypeId");

            migrationBuilder.AddPrimaryKey(
                name: "PK_Instants",
                table: "Instants",
                column: "Id");

            migrationBuilder.AddPrimaryKey(
                name: "PK_ExchangeRates",
                table: "ExchangeRates",
                column: "Id");

            migrationBuilder.AddPrimaryKey(
                name: "PK_CurrencyTypes",
                table: "CurrencyTypes",
                column: "Id");

            migrationBuilder.AddPrimaryKey(
                name: "PK_Countries",
                table: "Countries",
                column: "Id");

            migrationBuilder.AddForeignKey(
                name: "FK_Countries_CurrencyTypes_CurrencyTypeId",
                table: "Countries",
                column: "CurrencyTypeId",
                principalTable: "CurrencyTypes",
                principalColumn: "Id",
                onDelete: ReferentialAction.Restrict);

            migrationBuilder.AddForeignKey(
                name: "FK_ExchangeRates_CurrencyTypes_CurrencyTypeId",
                table: "ExchangeRates",
                column: "CurrencyTypeId",
                principalTable: "CurrencyTypes",
                principalColumn: "Id",
                onDelete: ReferentialAction.Restrict);

            migrationBuilder.AddForeignKey(
                name: "FK_ExchangeRates_Instants_InstantId",
                table: "ExchangeRates",
                column: "InstantId",
                principalTable: "Instants",
                principalColumn: "Id",
                onDelete: ReferentialAction.Restrict);
        }
    }
}
