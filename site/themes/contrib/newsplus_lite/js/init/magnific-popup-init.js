(function ($, Drupal, drupalSettings) {
  Drupal.behaviors.mtMagnificPopupFieldImage = {
    attach: function (context, settings) {
      $(context).find('.field--name-field-image a.image-popup').once('mtMagnificPopupFieldImageInit').magnificPopup({
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
})(jQuery, Drupal, drupalSettings);
