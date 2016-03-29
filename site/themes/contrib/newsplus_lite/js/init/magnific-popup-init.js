jQuery(document).ready(function($) {
  $(window).load(function() {

    $("a.image-popup").magnificPopup({
      type:"image",
      removalDelay: 300,
      mainClass: "mfp-fade",
      gallery: {
        enabled: true, // set to true to enable gallery
      }
    });
  });
});