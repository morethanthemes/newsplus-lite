<?php

/**
 * @file
 * Contains \Drupal\superfish\Form\SuperfishSettingsForm.
 */

namespace Drupal\superfish\Form;

use Drupal\Core\Config\ConfigFactoryInterface;
use Drupal\Core\Form\FormStateInterface;
use Drupal\Core\Form\ConfigFormBase;

/**
 * Superfish module configuration.
 */
class SuperfishSettingsForm extends ConfigFormBase {

  /**
   * {@inheritdoc}
   */
  public function getFormId() {
    return 'superfish_settings';
  }

  /**
   * A helper function to generate a list of paths to the Superfish library files.
   */
  public function superfish_library_path() {
    // Ensure the Libraries API module is installed and working.
    if (function_exists('libraries_get_path')) {
      $directory = libraries_get_path('superfish');
    }
    // Otherwise use the default directory.
    elseif (file_exists('profiles/' . drupal_get_profile() . '/libraries/superfish')) {
      $directory = 'profiles/' . drupal_get_profile() . '/libraries/superfish';
    }
    else {
      $directory = 'sites/all/libraries/superfish';
    }
    if (file_exists($directory)) {
      $output = $directory . "/jquery.hoverIntent.minified.js\r\n" .
        $directory . "/superfish.js\r\n" .
        $directory . "/supersubs.js\r\n" .
        $directory . "/supposition.js\r\n" .
        $directory . "/sfsmallscreen.js\r\n" .
        $directory . "/sftouchscreen.js";
    }
    else {
      $output = '';
    }
    return $output;
  }

  /**
   * Implements \Drupal\Core\Form\FormInterface::buildForm().
   */
  public function buildForm(array $form, FormStateInterface $form_state, $type = 'new') {
    $config = $this->config('superfish.settings');

    $form['superfish_library'] = array(
      '#type' => 'textarea',
      '#title' => t('Path to Superfish library'),
      '#description' => t('Edit only if you are sure of what you are doing.'),
      '#default_value' => $config->get('superfish_library'),
      '#rows' => 7,
    );

    return parent::buildForm($form, $form_state);
  }

  /**
   * Implements \Drupal\Core\Form\FormInterface::validateForm().
   */
  public function validateForm(array &$form, FormStateInterface $form_state) {
    $error = array();
    $sf_library = preg_replace("/(^[\r\n]*|[\r\n]+)[\s\t]*[\r\n]+/", "\n", trim($form_state->getValue('superfish_library')));
    if (empty($sf_library)) {
      $form_state->setErrorByName('superfish_library', t('Path to Superfish library field cannot be empty. Please try this list:') . str_replace("\r\n", ",", $this->superfish_library_path()));
    }
    else {
      // Trimming blank lines and such
      $sf_library = explode("\n", $sf_library);
      // Crystal clear
      foreach ($sf_library as $s) {
        if (!file_exists($s)) {
          $error[] = $s;
        }
      }
      if (!empty($error)) {
        $error_message = '';
        if (count($error) > 1) {
          foreach ($error as $e) {
            $error_message .= '<li>' . $e . '</li>';
          }
          $error_message = t('Files not found') . ': <ul>' . $error_message . '</ul>';
        }
        else {
          $error_message = t('File not found') . ': ' . $error[0];
        }
        $form_state->setErrorByName('superfish_library', $error_message);
      }
    }
    parent::validateForm($form, $form_state);
  }

  /**
   * Implements \Drupal\Core\Form\FormInterface::submitForm().
   */
  public function submitForm(array &$form, FormStateInterface $form_state) {

    $config = $this->config('superfish.settings');

    if ($form_state->hasValue('superfish_library')) {
      $config->set('superfish_library', $form_state->getValue('superfish_library'));
    }

    $config->save();

    parent::submitForm($form, $form_state);
  }

  /**
   * {@inheritdoc}
   */
  function getEditableConfigNames() {
    return ['superfish.settings'];
  }
}
