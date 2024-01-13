CREATE DATABASE currency

DROP TABLE [dbo].[Country];
DROP TABLE [dbo].[CurrencyType];
DROP TABLE [dbo].[ExchangeRate];
DROP TABLE [dbo].[Instant];

CREATE TABLE [dbo].[CurrencyType] (
    [id]   BIGINT   NOT NULL IDENTITY(1,1) PRIMARY KEY,
    [code] NVARCHAR (50) NULL,
    [name] NVARCHAR (50) NULL
);

CREATE TABLE [dbo].[Instant] (
    [id]   BIGINT   NOT NULL  IDENTITY(1,1) PRIMARY KEY,
    [time] DATETIME NULL
);

CREATE TABLE [dbo].[ExchangeRate] (
    [id]          BIGINT       NOT NULL  IDENTITY(1,1) PRIMARY KEY,
    [rate]       FLOAT NULL,
    [currency_id] BIGINT       NULL,
    [instant_id]  BIGINT       NULL,
    CONSTRAINT [FK_ExchangeCurrencyType] FOREIGN KEY ([currency_id]) REFERENCES [dbo].[CurrencyType] ([id]),
    CONSTRAINT [FK_ExchangeInstant] FOREIGN KEY ([instant_id]) REFERENCES [dbo].[Instant] ([id])
);

CREATE TABLE [dbo].[Country] (
    [id]          BIGINT       NOT NULL  IDENTITY(1,1) PRIMARY KEY,
    [name]        NVARCHAR (50) NULL,
    [currency_id] BIGINT       NULL,
    CONSTRAINT [FK_CountryCurrencyType] FOREIGN KEY ([currency_id]) REFERENCES [dbo].[CurrencyType] ([id]),    
);

SET IDENTITY_INSERT [dbo].[CurrencyType] ON
INSERT INTO [dbo].[CurrencyType] ([id], [code], [name]) VALUES (1, N'EUR', N'Euro')
INSERT INTO [dbo].[CurrencyType] ([id], [code], [name]) VALUES (2, N'USD', N'US Dollar')
INSERT INTO [dbo].[CurrencyType] ([id], [code], [name]) VALUES (3, N'JPY', N'Japanese Yen')
INSERT INTO [dbo].[CurrencyType] ([id], [code], [name]) VALUES (4, N'BGN', N'Bulgarian Lev')
INSERT INTO [dbo].[CurrencyType] ([id], [code], [name]) VALUES (5, N'CZK', N'Czech Koruna')
INSERT INTO [dbo].[CurrencyType] ([id], [code], [name]) VALUES (6, N'DKK', N'Danish Krone')
SET IDENTITY_INSERT [dbo].[CurrencyType] OFF


SET IDENTITY_INSERT [dbo].[Instant] ON
INSERT INTO [dbo].[Instant] ([id], [time]) VALUES (1, N'2020-09-01 00:00:00')
INSERT INTO [dbo].[Instant] ([id], [time]) VALUES (2, N'2020-08-01 00:00:00')
INSERT INTO [dbo].[Instant] ([id], [time]) VALUES (3, N'2020-07-01 00:00:00')
INSERT INTO [dbo].[Instant] ([id], [time]) VALUES (4, N'2020-06-01 00:00:00')
INSERT INTO [dbo].[Instant] ([id], [time]) VALUES (5, N'2020-05-01 00:00:00')
INSERT INTO [dbo].[Instant] ([id], [time]) VALUES (6, N'2020-04-01 00:00:00')
INSERT INTO [dbo].[Instant] ([id], [time]) VALUES (7, N'2020-03-01 00:00:00')
INSERT INTO [dbo].[Instant] ([id], [time]) VALUES (8, N'2020-02-01 00:00:00')
INSERT INTO [dbo].[Instant] ([id], [time]) VALUES (9, N'2020-01-01 00:00:00')
SET IDENTITY_INSERT [dbo].[Instant] OFF


SET IDENTITY_INSERT [dbo].[ExchangeRate] ON
INSERT INTO [dbo].[ExchangeRate] ([id], [rate], [currency_id], [instant_id]) VALUES (1, 1, 1, 1)
INSERT INTO [dbo].[ExchangeRate] ([id], [rate], [currency_id], [instant_id]) VALUES (2, 1.1702, 2, 1)
INSERT INTO [dbo].[ExchangeRate] ([id], [rate], [currency_id], [instant_id]) VALUES (3, 122.56, 3, 1)
INSERT INTO [dbo].[ExchangeRate] ([id], [rate], [currency_id], [instant_id]) VALUES (4, 19.558, 4, 1)
INSERT INTO [dbo].[ExchangeRate] ([id], [rate], [currency_id], [instant_id]) VALUES (5, 26.913, 5, 1)
INSERT INTO [dbo].[ExchangeRate] ([id], [rate], [currency_id], [instant_id]) VALUES (6, 7.4426, 6, 1)

INSERT INTO [dbo].[ExchangeRate] ([id], [rate], [currency_id], [instant_id]) VALUES (11, 1, 1, 2)
INSERT INTO [dbo].[ExchangeRate] ([id], [rate], [currency_id], [instant_id]) VALUES (21, 1.1702, 2, 2)
INSERT INTO [dbo].[ExchangeRate] ([id], [rate], [currency_id], [instant_id]) VALUES (31, 122.56, 3, 2)
INSERT INTO [dbo].[ExchangeRate] ([id], [rate], [currency_id], [instant_id]) VALUES (41, 19.558, 4, 2)
INSERT INTO [dbo].[ExchangeRate] ([id], [rate], [currency_id], [instant_id]) VALUES (51, 26.913, 5, 2)
INSERT INTO [dbo].[ExchangeRate] ([id], [rate], [currency_id], [instant_id]) VALUES (61, 7.4426, 6, 2)

INSERT INTO [dbo].[ExchangeRate] ([id], [rate], [currency_id], [instant_id]) VALUES (12, 1, 1, 3)
INSERT INTO [dbo].[ExchangeRate] ([id], [rate], [currency_id], [instant_id]) VALUES (22, 1.1702, 2, 3)
INSERT INTO [dbo].[ExchangeRate] ([id], [rate], [currency_id], [instant_id]) VALUES (32, 122.56, 3, 3)
INSERT INTO [dbo].[ExchangeRate] ([id], [rate], [currency_id], [instant_id]) VALUES (42, 19.558, 4, 3)
INSERT INTO [dbo].[ExchangeRate] ([id], [rate], [currency_id], [instant_id]) VALUES (52, 26.913, 5, 3)
INSERT INTO [dbo].[ExchangeRate] ([id], [rate], [currency_id], [instant_id]) VALUES (62, 7.4426, 6, 3)

INSERT INTO [dbo].[ExchangeRate] ([id], [rate], [currency_id], [instant_id]) VALUES (13, 1, 1, 4)
INSERT INTO [dbo].[ExchangeRate] ([id], [rate], [currency_id], [instant_id]) VALUES (23, 1.1702, 2, 4)
INSERT INTO [dbo].[ExchangeRate] ([id], [rate], [currency_id], [instant_id]) VALUES (33, 122.56, 3, 4)
INSERT INTO [dbo].[ExchangeRate] ([id], [rate], [currency_id], [instant_id]) VALUES (43, 19.558, 4, 4)
INSERT INTO [dbo].[ExchangeRate] ([id], [rate], [currency_id], [instant_id]) VALUES (53, 26.913, 5, 4)
INSERT INTO [dbo].[ExchangeRate] ([id], [rate], [currency_id], [instant_id]) VALUES (63, 7.4426, 6, 4)

INSERT INTO [dbo].[ExchangeRate] ([id], [rate], [currency_id], [instant_id]) VALUES (14, 1, 1, 5)
INSERT INTO [dbo].[ExchangeRate] ([id], [rate], [currency_id], [instant_id]) VALUES (24, 1.1702, 2, 5)
INSERT INTO [dbo].[ExchangeRate] ([id], [rate], [currency_id], [instant_id]) VALUES (34, 122.56, 3, 5)
INSERT INTO [dbo].[ExchangeRate] ([id], [rate], [currency_id], [instant_id]) VALUES (44, 19.558, 4, 5)
INSERT INTO [dbo].[ExchangeRate] ([id], [rate], [currency_id], [instant_id]) VALUES (54, 26.913, 5, 5)
INSERT INTO [dbo].[ExchangeRate] ([id], [rate], [currency_id], [instant_id]) VALUES (64, 7.4426, 6, 5)

INSERT INTO [dbo].[ExchangeRate] ([id], [rate], [currency_id], [instant_id]) VALUES (15, 1, 1, 6)
INSERT INTO [dbo].[ExchangeRate] ([id], [rate], [currency_id], [instant_id]) VALUES (25, 1.1702, 2, 6)
INSERT INTO [dbo].[ExchangeRate] ([id], [rate], [currency_id], [instant_id]) VALUES (35, 122.56, 3, 6)
INSERT INTO [dbo].[ExchangeRate] ([id], [rate], [currency_id], [instant_id]) VALUES (45, 19.558, 4, 6)
INSERT INTO [dbo].[ExchangeRate] ([id], [rate], [currency_id], [instant_id]) VALUES (55, 26.913, 5, 6)
INSERT INTO [dbo].[ExchangeRate] ([id], [rate], [currency_id], [instant_id]) VALUES (65, 7.4426, 6, 6)

INSERT INTO [dbo].[ExchangeRate] ([id], [rate], [currency_id], [instant_id]) VALUES (16, 1, 1, 7)
INSERT INTO [dbo].[ExchangeRate] ([id], [rate], [currency_id], [instant_id]) VALUES (26, 1.1702, 2, 7)
INSERT INTO [dbo].[ExchangeRate] ([id], [rate], [currency_id], [instant_id]) VALUES (36, 122.56, 3, 7)
INSERT INTO [dbo].[ExchangeRate] ([id], [rate], [currency_id], [instant_id]) VALUES (46, 19.558, 4, 7)
INSERT INTO [dbo].[ExchangeRate] ([id], [rate], [currency_id], [instant_id]) VALUES (56, 26.913, 5, 7)
INSERT INTO [dbo].[ExchangeRate] ([id], [rate], [currency_id], [instant_id]) VALUES (66, 7.4426, 6, 7)

INSERT INTO [dbo].[ExchangeRate] ([id], [rate], [currency_id], [instant_id]) VALUES (17, 1, 1, 8)
INSERT INTO [dbo].[ExchangeRate] ([id], [rate], [currency_id], [instant_id]) VALUES (27, 1.1702, 2, 8)
INSERT INTO [dbo].[ExchangeRate] ([id], [rate], [currency_id], [instant_id]) VALUES (37, 122.56, 3, 8)
INSERT INTO [dbo].[ExchangeRate] ([id], [rate], [currency_id], [instant_id]) VALUES (47, 19.558, 4, 8)
INSERT INTO [dbo].[ExchangeRate] ([id], [rate], [currency_id], [instant_id]) VALUES (57, 26.913, 5, 8)
INSERT INTO [dbo].[ExchangeRate] ([id], [rate], [currency_id], [instant_id]) VALUES (67, 7.4426, 6, 8)

INSERT INTO [dbo].[ExchangeRate] ([id], [rate], [currency_id], [instant_id]) VALUES (18, 1, 1, 9)
INSERT INTO [dbo].[ExchangeRate] ([id], [rate], [currency_id], [instant_id]) VALUES (28, 1.1702, 2, 9)
INSERT INTO [dbo].[ExchangeRate] ([id], [rate], [currency_id], [instant_id]) VALUES (38, 122.56, 3, 9)
INSERT INTO [dbo].[ExchangeRate] ([id], [rate], [currency_id], [instant_id]) VALUES (48, 19.558, 4, 9)
INSERT INTO [dbo].[ExchangeRate] ([id], [rate], [currency_id], [instant_id]) VALUES (58, 26.913, 5, 9)
INSERT INTO [dbo].[ExchangeRate] ([id], [rate], [currency_id], [instant_id]) VALUES (68, 7.4426, 6, 9)

SET IDENTITY_INSERT [dbo].[ExchangeRate] OFF


SET IDENTITY_INSERT [dbo].[Country] ON
INSERT INTO [dbo].[Country] ([id], [name], [currency_id]) VALUES (1, N'European Union', 1)
INSERT INTO [dbo].[Country] ([id], [name], [currency_id]) VALUES (2, N'United States of America', 2)
INSERT INTO [dbo].[Country] ([id], [name], [currency_id]) VALUES (3, N'Japan', 3)
INSERT INTO [dbo].[Country] ([id], [name], [currency_id]) VALUES (4, N'Bulgaria', 4)
INSERT INTO [dbo].[Country] ([id], [name], [currency_id]) VALUES (5, N'Czech Republic', 5)
INSERT INTO [dbo].[Country] ([id], [name], [currency_id]) VALUES (6, N'Denmark', 6)
SET IDENTITY_INSERT [dbo].[Country] OFF