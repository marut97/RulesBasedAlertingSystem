@echo OFF
devenv /clean debug RulesBasedAlertingSystem\RulesBasedAlertingSystem.sln
devenv /build debug RulesBasedAlertingSystem\RulesBasedAlertingSystem.sln
   set /p answer=Open in Registration Mode (Y/N)?
   if /i "%answer:~,1%" EQU "Y" RulesBasedAlertingSystem\Debug\RulesBasedAlertingSystem.Host.exe
   if /i "%answer:~,1%" EQU "N" exit /b
pause