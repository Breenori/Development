model = createpde('structural', 'static-solid');
importGeometry(model, 'hip_steel.stl')

figure
pdegplot(model, 'FaceLabels', 'off', 'FaceAlpha', 1);
view(30,30);
title("Modell mit eingezeichneten Flächen");

% BC
structuralProperties(model, "YoungsModulus", 210e3, "PoissonsRatio", 0.29);
structuralBC(model, "Face", 2, "Constraint", "fixed");
structuralBoundaryLoad(model, "Vertex", 14, "Force", [0;313.92;0]);

% Meshing 
mesh = generateMesh(model);
figure
pdeplot3D(model)
title("Diskretisiertes Modell");

% solving
result = solve(model);

maxY = max(result.Displacement.uy);
fprintf("Maximale Verschiebung in y-Richtung: %g m", maxY)

figure
pdeplot3D(model, 'ColorMapData', result.Displacement.y);
title('Knotenverschiebung in Meter')
colormap('jet')

figure
pdeplot3D(model, 'ColorMapData', result.VonMisesStress)
title('VonMises Vergleichsspannung')
colormap('jet')

% stress
figure
pdeplot3D(model, 'ColorMapData', result.Stress.yy);
title('Spannung')
colormap('jet')

figure
pdeplot3D(model, 'ColorMapData', result.Strain.yy)
title('Dehnung')
colormap('jet')


