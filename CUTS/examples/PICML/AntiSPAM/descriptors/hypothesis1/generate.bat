@setlocal
set ANTISPAM_DIR=%CUTS_ROOT%\examples\PICML\AntiSPAM

%CUTS_ROOT%\bin\gmet2m-exec -p %ANTISPAM_DIR%\AntiSPAM.xme --target=ComponentImplementations/TemplateAssembly -f hypothesis1-template-assembly%1.assembly --parser=GME_T2M_PICML_Assembly_Parser
%CUTS_ROOT%\bin\gmet2m-exec -p %ANTISPAM_DIR%\AntiSPAM.xme --target=DeploymentPlans -f hypothesis1-template-assembly.deployment --parser=GME_T2M_PICML_Deployment_Parser
%CUTS_ROOT%\bin\gmet2m-exec -p %ANTISPAM_DIR%\AntiSPAM.xme --run=MGA.Interpreter.DeploymentPlan --run-output=%ANTISPAM_DIR%\descriptors\hypothesis1 --run-focus=DeploymentPlans/TemplateDeployment
mv %ANTISPAM_DIR%\descriptors\hypothesis1\TemplateDeployment.cdp %ANTISPAM_DIR%\descriptors\hypothesis1\hypothesis1-template-assembly%1.cdp

@endlocal