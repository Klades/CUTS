#ifndef MOBIES_CUTS_export_H
#	define MOBIES_CUTS_export_H
#	ifndef CUTS_DSML_Export 
#		if defined (CUTS_HAS_DLL) && (CUTS_HAS_DLL == 1)
#			if defined (CUTS_EXPORT)
#				define CUTS_DSML_Export __declspec(dllexport)
#			else
#				define CUTS_DSML_Export __declspec(dllimport)
#			endif /* CUTS_EXPORT */
#		else
#			define CUTS_DSML_Export 
#		endif /* CUTS_HAS_DLL */
#	endif /* ifndef CUTS_DSML_Export  */
#endif /* MOBIES_CUTS_export_H */
