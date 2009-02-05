@rem $Id$

for /f %%a IN ('dir /b *.assembly') do call generate-single.bat %%~na
