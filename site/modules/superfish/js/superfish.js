(function ($, Drupal) {
  Drupal.behaviors.superfish = {
    attach(context, drupalSettings) {
      // Take a look at each menu to apply Superfish to.
      $.each(drupalSettings.superfish || {}, function (index, options) {
        const $menu = $(`ul#${options.id}`, context);

        // Check if we are to apply the Supersubs plug-in to it.
        if (options.plugins) {
          if (options.plugins.supersubs) {
            $menu.supersubs(options.plugins.supersubs);
          }
        }

        // Apply Superfish to the menu.
        $menu.superfish(options.sf);

        // Check if we are to apply any other plug-in to it.
        if (options.plugins) {
          if (options.plugins.touchscreen) {
            $menu.sftouchscreen(options.plugins.touchscreen);
          }
          if (options.plugins.smallscreen) {
            $menu.sfsmallscreen(options.plugins.smallscreen);
          }
          if (options.plugins.supposition) {
            $menu.supposition();
          }
        }
      });
    },
  };
})(jQuery, Drupal);
