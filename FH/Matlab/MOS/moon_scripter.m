
params = [0 20 40 30 50];
simparams = simget('Mars_Rover_Params');
[T, X, Y] = sim('Mars_Rover_Params', 100, simparams, params);
plot(T, Y)

