<?php
// $Id$
function fellowship_testimonials_settings_form($form, $form_state)
{
	$form['extensions']['testimonial_video'] = array(
		'#type' => 'textfield',
		'#title' => t('Allowed file extensions for uploading resource files'),
		'#description' => t('A comma separated list WITHOUT SPACE of source file extensions that are permitted to be uploaded on the server'),
		'#size' => 50,
		'#maxlength' => 255,
		'#required' => TRUE,
		'#default_value' => variable_get('resource_upload_extensions', '')
	);
	$form['extensions']['abstract_upload'] = array(
		'#type' => 'textfield',
		'#title' => t('Allowed file extensions for abstract'),
		'#description' => t('A comma separated list WITHOUT SPACE of pdf file extensions that are permitted to be uploaded on the server'),
		'#size' => 50,
		'#maxlength' => 255,
		'#required' => TRUE,
		'#default_value' => variable_get('fellowship_testimonials_abstract_upload_extensions', '')
	);
	$form['extensions']['fellowship_testimonials_upload'] = array(
		'#type' => 'textfield',
		'#title' => t('Allowed extensions for project files'),
		'#description' => t('A comma separated list WITHOUT SPACE of pdf file extensions that are permitted to be uploaded on the server'),
		'#size' => 50,
		'#maxlength' => 255,
		'#required' => TRUE,
		'#default_value' => variable_get('fellowship_testimonials_simulation_file', '')
	);
	$form['extensions']['fellowship_testimonials_script_upload'] = array(
		'#type' => 'textfield',
		'#title' => t('Allowed extensions for script files'),
		'#description' => t('A comma separated list WITHOUT SPACE of pdf file extensions that are permitted to be uploaded on the server'),
		'#size' => 50,
		'#maxlength' => 255,
		'#required' => TRUE,
		'#default_value' => variable_get('fellowship_testimonials_script_file', '')
	);
	$form['submit'] = array(
		'#type' => 'submit',
		'#value' => t('Submit')
	);
	return $form;
}
function fellowship_testimonials_settings_form_validate($form, &$form_state)
{
	return;
}
function fellowship_testimonials_settings_form_submit($form, &$form_state)
{
	variable_set('fellowship_testimonials_emails', $form_state['values']['emails']);
	variable_set('fellowship_testimonials_cc_emails', $form_state['values']['cc_emails']);
	variable_set('fellowship_testimonials_from_email', $form_state['values']['from_email']);
	variable_set('resource_upload_extensions', $form_state['values']['resource_upload']);
	variable_set('fellowship_testimonials_abstract_upload_extensions', $form_state['values']['abstract_upload']);
	variable_set('fellowship_testimonials_simulation_file', $form_state['values']['fellowship_testimonials_upload']);
	variable_set('fellowship_testimonials_script_file', $form_state['values']['fellowship_testimonials_script_upload']);
	drupal_set_message(t('Settings updated'), 'status');
}