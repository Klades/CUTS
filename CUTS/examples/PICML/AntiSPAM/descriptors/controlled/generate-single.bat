@setlocal
set GME_FILE=%~dp0..\..\AntiSPAM.xme

%CUTS_ROOT%\bin\gmet2m-exec -p %GME_FILE% --target=ComponentImplementations/TemplateAssembly -f %~dp0%1.assembly --parser=GME_T2M_PICML_Assembly_Parser
%CUTS_ROOT%\bin\gmet2m-exec -p %GME_FILE% --target=DeploymentPlans -f %~dp0%1.deployment --parser=GME_T2M_PICML_Deployment_Parser
%CUTS_ROOT%\bin\gmet2m-exec -p %GME_FILE% --run=MGA.Interpreter.DeploymentPlan --run-output=%~dp0 --run-focus=DeploymentPlans/TemplateDeployment
mv %~dp0TemplateDeployment.cdp %~dp0%1.cdp

@endlocal