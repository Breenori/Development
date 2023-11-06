install.packages(c('caret', 'Metrics'),dependencies = T)
library(tidyverse)
library(caret)
library(Metrics)

setwd("D:\\Projects\\Git\\Development\\FH\\Python\\CO2\\T3")
rsq <- function (x, y) cor(x, y) ^ 2



train = read.csv2("splits/training.csv", sep=",")
train$x1 = as.numeric(train$x1)
train$x2 = as.numeric(train$x2)
train$x3 = as.numeric(train$x3)
train$x4 = as.numeric(train$x4)
train$y = as.numeric(train$y)

set.seed(4243)

data_rows <- floor(0.80 * nrow(train))
train_indices <- sample(c(1:nrow(train)), data_rows)
train_data <- train[train_indices,]
val_data <- train[-train_indices,]

test_inter = read.csv2("splits/inter_total.csv", sep=",")
test_inter$x1 = as.numeric(test_inter$x1)
test_inter$x2 = as.numeric(test_inter$x2)
test_inter$x3 = as.numeric(test_inter$x3)
test_inter$x4 = as.numeric(test_inter$x4)
test_inter$y = as.numeric(test_inter$y)
test_extra = read.csv2("splits/extrapolation.csv", sep=",")
test_extra$x1 = as.numeric(test_extra$x1)
test_extra$x2 = as.numeric(test_extra$x2)
test_extra$x3 = as.numeric(test_extra$x3)
test_extra$x4 = as.numeric(test_extra$x4)
test_extra$y = as.numeric(test_extra$y)

# Build the model
model <- lm(y ~ poly(x1, 5) + poly(x2, 5) + poly(x3, 5) + poly(x4, 5), data = train_data)

pred_val <- model %>% predict(val_data)
data.frame(MAE = mae(pred_val, val_data$y),
           R2 = rsq(pred_val, val_data$y),
           MSE = mse(pred_val, val_data$y))

pred_inter <- model %>% predict(test_inter)
data.frame(MAE = mae(pred_inter, test_inter$y),
           R2 = rsq(pred_inter, test_inter$y),
           MSE = mse(pred_inter, test_inter$y))

pred_extra <- model %>% predict(test_extra)
data.frame(MAE = mae(pred_extra, test_extra$y),
           R2 = rsq(pred_extra, test_extra$y),
           MSE = mse(pred_extra, test_extra$y))
