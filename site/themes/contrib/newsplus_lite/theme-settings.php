<?php

function newsplus_lite_form_system_theme_settings_alter(&$form, &$form_state) {

  $form['#attached']['library'][] = 'newsplus_lite/theme-settings';

  $form['mtt_settings'] = array(
    '#type' => 'fieldset',
    '#title' => t('MtT Theme Settings'),
    '#collapsible' => FALSE,
    '#collapsed' => FALSE,
  );

  $form['mtt_settings']['tabs'] = array(
    '#type' => 'vertical_tabs',
    '#default_tab' => 'basic_tab',
  );

  $form['mtt_settings']['basic_tab']['basic_settings'] = array(
    '#type' => 'details',
    '#title' => t('Basic Settings'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
    '#group' => 'tabs',
  );

  $form['mtt_settings']['basic_tab']['basic_settings']['header'] = array(
   '#type' => 'item',
   '#markup' => '<div class="theme-settings-title">'.t("Header positioning").'</div>',
  );

  $form['mtt_settings']['basic_tab']['basic_settings']['fixed_header'] = array(
    '#type' => 'checkbox',
    '#title' => t('Fixed position'),
    '#description'   => t('Use the checkbox to apply fixed position to the header.'),
    '#default_value' => theme_get_setting('fixed_header', 'newsplus_lite'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );

  $form['mtt_settings']['basic_tab']['basic_settings']['scrolltop'] = array(
    '#type' => 'item',
    '#markup' => '<div class="theme-settings-title">'.t("Scroll to top").'</div>',
  );

  $form['mtt_settings']['basic_tab']['basic_settings']['scrolltop_display'] = array(
    '#type' => 'checkbox',
    '#title' => t('Show scroll-to-top button'),
    '#description'   => t('Use the checkbox to enable or disable scroll-to-top button.'),
    '#default_value' => theme_get_setting('scrolltop_display', 'newsplus_lite'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );

  $form['mtt_settings']['bootstrap_tab']['bootstrap'] = array(
    '#type' => 'details',
    '#title' => t('Bootstrap'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
    '#group' => 'tabs',
  );

  $form['mtt_settings']['bootstrap_tab']['bootstrap']['bootstrap_remote_type'] = array(
    '#type' => 'select',
    '#title' => t('Select the remote type'),
    '#description'   => t('From the drop down select box, select how to load the Bootstrap library. If you select "Local" make sure that you download and place Bootstrap folder into the root theme folder (newsplus_lite/bootstrap).'),
    '#default_value' => theme_get_setting('bootstrap_remote_type', 'newsplus_lite'),
    '#options' => array(
    'local' => t('Local / No remote'),
    'cdn' => t('CDN'),
    ),
  );

  $form['mtt_settings']['premium_tab']['premium'] = array(
    '#type' => 'details',
    '#title' => t('Premium version'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
    '#group' => 'tabs',
  );

  $form['mtt_settings']['premium_tab']['premium']['premium_description'] = array(
   '#type' => 'item',
   '#markup' =>
   '<div class="theme-settings-title">'.t("Get the premium version of this theme").'</div>
   <div class="theme-settings-image-wrapper">
   <a href="http://morethanthemes.com/themes/newsplus?utm_source=newsplus-lite-demo&utm_medium=theme-settings&utm_campaign=free-themes" target="_blank">
   <img src="' . base_path() . drupal_get_path('theme', 'newsplus_lite') . '/images/premium.jpg" />
   </a></div> ',
  );

}
