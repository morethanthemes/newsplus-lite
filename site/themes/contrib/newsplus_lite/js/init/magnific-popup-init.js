(function ($, Drupal, drupalSettings, once) {
  Drupal.behaviors.mtMagnificPopupFieldImage = {
    attach: function (context, settings) {
      const element = once('mtMagnificPopupFieldImageInit', ".field--name-field-image a.image-popup", context);
      $(element).magnificPopup({
        type:"image",
        removalDelay: 300,
        mainClass: "mfp-fade",
        gallery: {
          enabled: true, // set to true to enable gallery
        },
        image: {
          titleSrc: function(item) {
            return item.el.children()[0].title || '';
          }
        }
      });
    }
  };
})(jQuery, Drupal, drupalSettings, once);