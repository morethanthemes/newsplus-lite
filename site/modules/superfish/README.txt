CONTENTS OF THIS FILE
---------------------

 * Introduction
 * Requirements
 * Recommended Modules
 * Installation
 * Configuration
 * Maintainers


INTRODUCTION
------------

This module allows for integration of jQuery Superfish plug-in with Drupal CMS.

 * For a full description of the module, visit the project page:
   https://www.drupal.org/project/superfish

 * To submit bug reports and feature suggestions, or to track changes:
   https://www.drupal.org/project/issues/superfish


REQUIREMENTS
------------

This module requires the following outside of Drupal core:

 * Superfish library - https://github.com/mehrpadin/Superfish-for-Drupal/


RECOMMENDED MODULES
-------------------

 * Libraries API - https://www.drupal.org/project/libraries
 * jQuery Easing plugin - https://www.drupal.org/project/jqeasing


INSTALLATION
------------

 * Install the Superfish module as you would normally install a contributed
   Drupal module. Visit
   https://www.drupal.org/node/1897420 for further information.


CONFIGURATION
-------------

    1. Navigate to Administration > Extend and enable the module.
    2. Go to Administation > Structure > Block layout > select a Place block
       button to add a Superfish block to a region.
    3. Use the "Configure" link of the block to configure it accordingly to your
       needs.

How to style:
    1. In the block configuration page, set the Style to None
    2. Copy one of the Superfish sample styles, for example default.css from
       sites/all/libraries/superfish/style to your theme; either as a separate
       CSS file or part of the main CSS file of your theme.
    3. Rename the selectors .sf-style-default to .sf-style-none or remove
       them altogether.
    4. You are now ready to unleash your CSS artistry :)

Some design tips:
 * Utilize a DOM inspector (such as Firefox Developer Tools) for temporarily
   modifying live code in real time.
 * Set the Mouse delay of the block settings to 99999999 so the sub-menus will
   stay open for a longer time giving you more time to work with them in the
   DOM inspector etc.
   Useful links:
	 https://docs.acquia.com/resource/browser-tool/
	 https://www.drupal.org/node/147789#web-browser-tools


MAINTAINERS
-----------

 * mehrpadin - https://www.drupal.org/u/mehrpadin
