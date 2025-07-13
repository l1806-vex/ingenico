//! \file        X509_.h
//! \brief This module contains all the definitions to manage a public key infrastructure (PKI) for SSL.
//!
/*! @defgroup KSFAM_X509 PKI Management functions
 @ingroup KSFAM_SSL
 @brief PKI management functions (X509 certificates, RSA key generation...).  
 @{
**/

#ifndef __PACKSSL_COMPONENT_X509__
#define __PACKSSL_COMPONENT_X509__

/**
\cond
avoid dox documentation */
#ifndef NID_undef		

/*
======================================================================
                                        List of Defines
======================================================================
*/
#define SN_undef			"UNDEF"
#define LN_undef			"undefined"
#define NID_undef			0
#define OBJ_undef			0L

#define SN_Algorithm			"Algorithm"
#define LN_algorithm			"algorithm"
#define NID_algorithm			38
#define OBJ_algorithm			1L,3L,14L,3L,2L

#define LN_rsadsi			"rsadsi"
#define NID_rsadsi			1
#define OBJ_rsadsi			1L,2L,840L,113549L

#define LN_pkcs				"pkcs"
#define NID_pkcs			2
#define OBJ_pkcs			OBJ_rsadsi,1L

#define SN_md2				"MD2"
#define LN_md2				"md2"
#define NID_md2				3
#define OBJ_md2				OBJ_rsadsi,2L,2L

#define SN_md5				"MD5"
#define LN_md5				"md5"
#define NID_md5				4
#define OBJ_md5				OBJ_rsadsi,2L,5L

#define SN_rc4				"RC4"
#define LN_rc4				"rc4"
#define NID_rc4				5
#define OBJ_rc4				OBJ_rsadsi,3L,4L

#define LN_rsaEncryption		"rsaEncryption"
#define NID_rsaEncryption		6
#define OBJ_rsaEncryption		OBJ_pkcs,1L,1L

#define SN_md2WithRSAEncryption		"RSA-MD2"
#define LN_md2WithRSAEncryption		"md2WithRSAEncryption"
#define NID_md2WithRSAEncryption	7
#define OBJ_md2WithRSAEncryption	OBJ_pkcs,1L,2L

#define SN_md5WithRSAEncryption		"RSA-MD5"
#define LN_md5WithRSAEncryption		"md5WithRSAEncryption"
#define NID_md5WithRSAEncryption	8
#define OBJ_md5WithRSAEncryption	OBJ_pkcs,1L,4L

#define SN_pbeWithMD2AndDES_CBC		"PBE-MD2-DES"
#define LN_pbeWithMD2AndDES_CBC		"pbeWithMD2AndDES-CBC"
#define NID_pbeWithMD2AndDES_CBC	9
#define OBJ_pbeWithMD2AndDES_CBC	OBJ_pkcs,5L,1L

#define SN_pbeWithMD5AndDES_CBC		"PBE-MD5-DES"
#define LN_pbeWithMD5AndDES_CBC		"pbeWithMD5AndDES-CBC"
#define NID_pbeWithMD5AndDES_CBC	10
#define OBJ_pbeWithMD5AndDES_CBC	OBJ_pkcs,5L,3L

#define LN_X500				"X500"
#define NID_X500			11
#define OBJ_X500			2L,5L

#define LN_X509				"X509"
#define NID_X509			12
#define OBJ_X509			OBJ_X500,4L

#define SN_commonName			"CN"
#define LN_commonName			"commonName"
#define NID_commonName			13
#define OBJ_commonName			OBJ_X509,3L

#define SN_countryName			"C"
#define LN_countryName			"countryName"
#define NID_countryName			14
#define OBJ_countryName			OBJ_X509,6L

#define SN_localityName			"L"
#define LN_localityName			"localityName"
#define NID_localityName		15
#define OBJ_localityName		OBJ_X509,7L

/* Postal Address PA */

/* should be "ST" (rfc1327) but MS uses 'S' */
#define SN_stateOrProvinceName		"ST"
#define LN_stateOrProvinceName		"stateOrProvinceName"
#define NID_stateOrProvinceName		16
#define OBJ_stateOrProvinceName		OBJ_X509,8L

#define SN_organizationName		"O"
#define LN_organizationName		"organizationName"
#define NID_organizationName		17
#define OBJ_organizationName		OBJ_X509,10L

#define SN_organizationalUnitName	"OU"
#define LN_organizationalUnitName	"organizationalUnitName"
#define NID_organizationalUnitName	18
#define OBJ_organizationalUnitName	OBJ_X509,11L

#define SN_rsa				"RSA"
#define LN_rsa				"rsa"
#define NID_rsa				19
#define OBJ_rsa				OBJ_X500,8L,1L,1L

#define LN_pkcs7			"pkcs7"
#define NID_pkcs7			20
#define OBJ_pkcs7			OBJ_pkcs,7L

#define LN_pkcs7_data			"pkcs7-data"
#define NID_pkcs7_data			21
#define OBJ_pkcs7_data			OBJ_pkcs7,1L

#define LN_pkcs7_signed			"pkcs7-signedData"
#define NID_pkcs7_signed		22
#define OBJ_pkcs7_signed		OBJ_pkcs7,2L

#define LN_pkcs7_enveloped		"pkcs7-envelopedData"
#define NID_pkcs7_enveloped		23
#define OBJ_pkcs7_enveloped		OBJ_pkcs7,3L

#define LN_pkcs7_signedAndEnveloped	"pkcs7-signedAndEnvelopedData"
#define NID_pkcs7_signedAndEnveloped	24
#define OBJ_pkcs7_signedAndEnveloped	OBJ_pkcs7,4L

#define LN_pkcs7_digest			"pkcs7-digestData"
#define NID_pkcs7_digest		25
#define OBJ_pkcs7_digest		OBJ_pkcs7,5L

#define LN_pkcs7_encrypted		"pkcs7-encryptedData"
#define NID_pkcs7_encrypted		26
#define OBJ_pkcs7_encrypted		OBJ_pkcs7,6L

#define LN_pkcs3			"pkcs3"
#define NID_pkcs3			27
#define OBJ_pkcs3			OBJ_pkcs,3L

#define LN_dhKeyAgreement		"dhKeyAgreement"
#define NID_dhKeyAgreement		28
#define OBJ_dhKeyAgreement		OBJ_pkcs3,1L

#define SN_des_ecb			"DES-ECB"
#define LN_des_ecb			"des-ecb"
#define NID_des_ecb			29
#define OBJ_des_ecb			OBJ_algorithm,6L

#define SN_des_cfb64			"DES-CFB"
#define LN_des_cfb64			"des-cfb"
#define NID_des_cfb64			30
/* IV + num */
#define OBJ_des_cfb64			OBJ_algorithm,9L

#define SN_des_cbc			"DES-CBC"
#define LN_des_cbc			"des-cbc"
#define NID_des_cbc			31
/* IV */
#define OBJ_des_cbc			OBJ_algorithm,7L

#define SN_des_ede			"DES-EDE"
#define LN_des_ede			"des-ede"
#define NID_des_ede			32
#define OBJ_des_ede			OBJ_algorithm,17L

#define SN_des_ede3			"DES-EDE3"
#define LN_des_ede3			"des-ede3"
#define NID_des_ede3			33

#define SN_idea_cbc			"IDEA-CBC"
#define LN_idea_cbc			"idea-cbc"
#define NID_idea_cbc			34
#define OBJ_idea_cbc			1L,3L,6L,1L,4L,1L,188L,7L,1L,1L,2L

#define SN_idea_cfb64			"IDEA-CFB"
#define LN_idea_cfb64			"idea-cfb"
#define NID_idea_cfb64			35

#define SN_idea_ecb			"IDEA-ECB"
#define LN_idea_ecb			"idea-ecb"
#define NID_idea_ecb			36

#define SN_rc2_cbc			"RC2-CBC"
#define LN_rc2_cbc			"rc2-cbc"
#define NID_rc2_cbc			37
#define OBJ_rc2_cbc			OBJ_rsadsi,3L,2L

#define SN_rc2_ecb			"RC2-ECB"
#define LN_rc2_ecb			"rc2-ecb"
#define NID_rc2_ecb			38

#define SN_rc2_cfb64			"RC2-CFB"
#define LN_rc2_cfb64			"rc2-cfb"
#define NID_rc2_cfb64			39

#define SN_rc2_ofb64			"RC2-OFB"
#define LN_rc2_ofb64			"rc2-ofb"
#define NID_rc2_ofb64			40

#define SN_sha				"SHA"
#define LN_sha				"sha"
#define NID_sha				41
#define OBJ_sha				OBJ_algorithm,18L

#define SN_shaWithRSAEncryption		"RSA-SHA"
#define LN_shaWithRSAEncryption		"shaWithRSAEncryption"
#define NID_shaWithRSAEncryption	42
#define OBJ_shaWithRSAEncryption	OBJ_algorithm,15L

#define SN_des_ede_cbc			"DES-EDE-CBC"
#define LN_des_ede_cbc			"des-ede-cbc"
#define NID_des_ede_cbc			43

#define SN_des_ede3_cbc			"DES-EDE3-CBC"
#define LN_des_ede3_cbc			"des-ede3-cbc"
#define NID_des_ede3_cbc		44
#define OBJ_des_ede3_cbc		OBJ_rsadsi,3L,7L

#define SN_des_ofb64			"DES-OFB"
#define LN_des_ofb64			"des-ofb"
#define NID_des_ofb64			45
#define OBJ_des_ofb64			OBJ_algorithm,8L

#define SN_idea_ofb64			"IDEA-OFB"
#define LN_idea_ofb64			"idea-ofb"
#define NID_idea_ofb64			46

#define LN_pkcs9			"pkcs9"
#define NID_pkcs9			47
#define OBJ_pkcs9			OBJ_pkcs,9L

#define SN_pkcs9_emailAddress		"Email"
#define LN_pkcs9_emailAddress		"emailAddress"
#define NID_pkcs9_emailAddress		48
#define OBJ_pkcs9_emailAddress		OBJ_pkcs9,1L

#define LN_pkcs9_unstructuredName	"unstructuredName"
#define NID_pkcs9_unstructuredName	49
#define OBJ_pkcs9_unstructuredName	OBJ_pkcs9,2L

#define LN_pkcs9_contentType		"contentType"
#define NID_pkcs9_contentType		50
#define OBJ_pkcs9_contentType		OBJ_pkcs9,3L

#define LN_pkcs9_messageDigest		"messageDigest"
#define NID_pkcs9_messageDigest		51
#define OBJ_pkcs9_messageDigest		OBJ_pkcs9,4L

#define LN_pkcs9_signingTime		"signingTime"
#define NID_pkcs9_signingTime		52
#define OBJ_pkcs9_signingTime		OBJ_pkcs9,5L

#define LN_pkcs9_countersignature	"countersignature"
#define NID_pkcs9_countersignature	53
#define OBJ_pkcs9_countersignature	OBJ_pkcs9,6L

#define LN_pkcs9_challengePassword	"challengePassword"
#define NID_pkcs9_challengePassword	54
#define OBJ_pkcs9_challengePassword	OBJ_pkcs9,7L

#define LN_pkcs9_unstructuredAddress	"unstructuredAddress"
#define NID_pkcs9_unstructuredAddress	55
#define OBJ_pkcs9_unstructuredAddress	OBJ_pkcs9,8L

#define LN_pkcs9_extCertAttributes	"extendedCertificateAttributes"
#define NID_pkcs9_extCertAttributes	56
#define OBJ_pkcs9_extCertAttributes	OBJ_pkcs9,9L

#define SN_netscape			"Netscape"
#define LN_netscape			"Netscape Communications Corp."
#define NID_netscape			57
#define OBJ_netscape			2L,16L,840L,1L,113730L

#define SN_netscape_cert_extension	"nsCertExt"
#define LN_netscape_cert_extension	"Netscape Certificate Extension"
#define NID_netscape_cert_extension	58
#define OBJ_netscape_cert_extension	OBJ_netscape,1L

#define SN_netscape_data_type		"nsDataType"
#define LN_netscape_data_type		"Netscape Data Type"
#define NID_netscape_data_type		59
#define OBJ_netscape_data_type		OBJ_netscape,2L

#define SN_des_ede_cfb64		"DES-EDE-CFB"
#define LN_des_ede_cfb64		"des-ede-cfb"
#define NID_des_ede_cfb64		60

#define SN_des_ede3_cfb64		"DES-EDE3-CFB"
#define LN_des_ede3_cfb64		"des-ede3-cfb"
#define NID_des_ede3_cfb64		61

#define SN_des_ede_ofb64		"DES-EDE-OFB"
#define LN_des_ede_ofb64		"des-ede-ofb"
#define NID_des_ede_ofb64		62

#define SN_des_ede3_ofb64		"DES-EDE3-OFB"
#define LN_des_ede3_ofb64		"des-ede3-ofb"
#define NID_des_ede3_ofb64		63

#define SN_sha1				"SHA1"
#define LN_sha1				"sha1"
#define NID_sha1			64
#define OBJ_sha1			OBJ_algorithm,26L
/* 28 Jun 1996 - eay */
/* #define OBJ_sha1			1L,3L,14L,2L,26L,05L <- wrong */

#define SN_sha1WithRSAEncryption	"RSA-SHA1"
#define LN_sha1WithRSAEncryption	"sha1WithRSAEncryption"
#define NID_sha1WithRSAEncryption	65
#define OBJ_sha1WithRSAEncryption	OBJ_pkcs,1L,5L

#define SN_dsaWithSHA			"DSA-SHA"
#define LN_dsaWithSHA			"dsaWithSHA"
#define NID_dsaWithSHA			66
#define OBJ_dsaWithSHA			OBJ_algorithm,13L

#define SN_dsa_2			"DSA-old"
#define LN_dsa_2			"dsaEncryption-old"
#define NID_dsa_2			67
#define OBJ_dsa_2			OBJ_algorithm,12L

/* proposed by microsoft to RSA */
#define SN_pbeWithSHA1AndRC2_CBC	"PBE-SHA1-RC2-64"
#define LN_pbeWithSHA1AndRC2_CBC	"pbeWithSHA1AndRC2-CBC"
#define NID_pbeWithSHA1AndRC2_CBC	68
#define OBJ_pbeWithSHA1AndRC2_CBC	OBJ_pkcs,5L,11L 

/* proposed by microsoft to RSA as pbeWithSHA1AndRC4: it is now
 * defined explicitly in PKCS#5 v2.0 as id-PBKDF2 which is something
 * completely different.
 */
#define LN_id_pbkdf2			"PBKDF2"
#define NID_id_pbkdf2			69
#define OBJ_id_pbkdf2			OBJ_pkcs,5L,12L 

#define SN_dsaWithSHA1_2		"DSA-SHA1-old"
#define LN_dsaWithSHA1_2		"dsaWithSHA1-old"
#define NID_dsaWithSHA1_2		70
/* taken from 'sdn706r20.pdf' which is actually an NSA document :-) */
#define OBJ_dsaWithSHA1_2		OBJ_algorithm,27L

#define SN_netscape_cert_type		"nsCertType"
#define LN_netscape_cert_type		"Netscape Cert Type"
#define NID_netscape_cert_type		71
#define OBJ_netscape_cert_type		OBJ_netscape_cert_extension,1L

#define SN_netscape_base_url		"nsBaseUrl"
#define LN_netscape_base_url		"Netscape Base Url"
#define NID_netscape_base_url		72
#define OBJ_netscape_base_url		OBJ_netscape_cert_extension,2L

#define SN_netscape_revocation_url	"nsRevocationUrl"
#define LN_netscape_revocation_url	"Netscape Revocation Url"
#define NID_netscape_revocation_url	73
#define OBJ_netscape_revocation_url	OBJ_netscape_cert_extension,3L

#define SN_netscape_ca_revocation_url	"nsCaRevocationUrl"
#define LN_netscape_ca_revocation_url	"Netscape CA Revocation Url"
#define NID_netscape_ca_revocation_url	74
#define OBJ_netscape_ca_revocation_url	OBJ_netscape_cert_extension,4L

#define SN_netscape_renewal_url		"nsRenewalUrl"
#define LN_netscape_renewal_url		"Netscape Renewal Url"
#define NID_netscape_renewal_url	75
#define OBJ_netscape_renewal_url	OBJ_netscape_cert_extension,7L

#define SN_netscape_ca_policy_url	"nsCaPolicyUrl"
#define LN_netscape_ca_policy_url	"Netscape CA Policy Url"
#define NID_netscape_ca_policy_url	76
#define OBJ_netscape_ca_policy_url	OBJ_netscape_cert_extension,8L

#define SN_netscape_ssl_server_name	"nsSslServerName"
#define LN_netscape_ssl_server_name	"Netscape SSL Server Name"
#define NID_netscape_ssl_server_name	77
#define OBJ_netscape_ssl_server_name	OBJ_netscape_cert_extension,12L

#define SN_netscape_comment		"nsComment"
#define LN_netscape_comment		"Netscape Comment"
#define NID_netscape_comment		78
#define OBJ_netscape_comment		OBJ_netscape_cert_extension,13L

#define SN_netscape_cert_sequence	"nsCertSequence"
#define LN_netscape_cert_sequence	"Netscape Certificate Sequence"
#define NID_netscape_cert_sequence	79
#define OBJ_netscape_cert_sequence	OBJ_netscape_data_type,5L

#define SN_desx_cbc			"DESX-CBC"
#define LN_desx_cbc			"desx-cbc"
#define NID_desx_cbc			80

#define SN_id_ce			"id-ce"
#define NID_id_ce			81
#define OBJ_id_ce			2L,5L,29L

#define SN_subject_key_identifier	"subjectKeyIdentifier"
#define LN_subject_key_identifier	"X509v3 Subject Key Identifier"
#define NID_subject_key_identifier	82
#define OBJ_subject_key_identifier	OBJ_id_ce,14L

#define SN_key_usage			"keyUsage"
#define LN_key_usage			"X509v3 Key Usage"
#define NID_key_usage			83
#define OBJ_key_usage			OBJ_id_ce,15L

#define SN_private_key_usage_period	"privateKeyUsagePeriod"
#define LN_private_key_usage_period	"X509v3 Private Key Usage Period"
#define NID_private_key_usage_period	84
#define OBJ_private_key_usage_period	OBJ_id_ce,16L

#define SN_subject_alt_name		"subjectAltName"
#define LN_subject_alt_name		"X509v3 Subject Alternative Name"
#define NID_subject_alt_name		85
#define OBJ_subject_alt_name		OBJ_id_ce,17L

#define SN_issuer_alt_name		"issuerAltName"
#define LN_issuer_alt_name		"X509v3 Issuer Alternative Name"
#define NID_issuer_alt_name		86
#define OBJ_issuer_alt_name		OBJ_id_ce,18L

#define SN_basic_constraints		"basicConstraints"
#define LN_basic_constraints		"X509v3 Basic Constraints"
#define NID_basic_constraints		87
#define OBJ_basic_constraints		OBJ_id_ce,19L

#define SN_crl_number			"crlNumber"
#define LN_crl_number			"X509v3 CRL Number"
#define NID_crl_number			88
#define OBJ_crl_number			OBJ_id_ce,20L

#define SN_certificate_policies		"certificatePolicies"
#define LN_certificate_policies		"X509v3 Certificate Policies"
#define NID_certificate_policies	89
#define OBJ_certificate_policies	OBJ_id_ce,32L

#define SN_authority_key_identifier	"authorityKeyIdentifier"
#define LN_authority_key_identifier	"X509v3 Authority Key Identifier"
#define NID_authority_key_identifier	90
#define OBJ_authority_key_identifier	OBJ_id_ce,35L

#define SN_bf_cbc			"BF-CBC"
#define LN_bf_cbc			"bf-cbc"
#define NID_bf_cbc			91
#define OBJ_bf_cbc			1L,3L,6L,1L,4L,1L,3029L,1L,2L

#define SN_bf_ecb			"BF-ECB"
#define LN_bf_ecb			"bf-ecb"
#define NID_bf_ecb			92

#define SN_bf_cfb64			"BF-CFB"
#define LN_bf_cfb64			"bf-cfb"
#define NID_bf_cfb64			93

#define SN_bf_ofb64			"BF-OFB"
#define LN_bf_ofb64			"bf-ofb"
#define NID_bf_ofb64			94

#define SN_mdc2				"MDC2"
#define LN_mdc2				"mdc2"
#define NID_mdc2			95
#define OBJ_mdc2			2L,5L,8L,3L,101L
/* An alternative?			1L,3L,14L,3L,2L,19L */

#define SN_mdc2WithRSA			"RSA-MDC2"
#define LN_mdc2WithRSA			"mdc2withRSA"
#define NID_mdc2WithRSA			96
#define OBJ_mdc2WithRSA			2L,5L,8L,3L,100L

#define SN_rc4_40			"RC4-40"
#define LN_rc4_40			"rc4-40"
#define NID_rc4_40			97

#define SN_rc2_40_cbc			"RC2-40-CBC"
#define LN_rc2_40_cbc			"rc2-40-cbc"
#define NID_rc2_40_cbc			98

#define SN_givenName			"G"
#define LN_givenName			"givenName"
#define NID_givenName			99
#define OBJ_givenName			OBJ_X509,42L

#define SN_surname			"S"
#define LN_surname			"surname"
#define NID_surname			100
#define OBJ_surname			OBJ_X509,4L

#define SN_initials			"I"
#define LN_initials			"initials"
#define NID_initials			101
#define OBJ_initials			OBJ_X509,43L

#define SN_uniqueIdentifier		"UID"
#define LN_uniqueIdentifier		"uniqueIdentifier"
#define NID_uniqueIdentifier		102
#define OBJ_uniqueIdentifier		OBJ_X509,45L

#define SN_crl_distribution_points	"crlDistributionPoints"
#define LN_crl_distribution_points	"X509v3 CRL Distribution Points"
#define NID_crl_distribution_points	103
#define OBJ_crl_distribution_points	OBJ_id_ce,31L

#define SN_md5WithRSA			"RSA-NP-MD5"
#define LN_md5WithRSA			"md5WithRSA"
#define NID_md5WithRSA			104
#define OBJ_md5WithRSA			OBJ_algorithm,3L

#define SN_serialNumber			"SN"
#define LN_serialNumber			"serialNumber"
#define NID_serialNumber		105
#define OBJ_serialNumber		OBJ_X509,5L

#define SN_title			"T"
#define LN_title			"title"
#define NID_title			106
#define OBJ_title			OBJ_X509,12L

#define SN_description			"D"
#define LN_description			"description"
#define NID_description			107
#define OBJ_description			OBJ_X509,13L

/* CAST5 is CAST-128, I'm just sticking with the documentation */
#define SN_cast5_cbc			"CAST5-CBC"
#define LN_cast5_cbc			"cast5-cbc"
#define NID_cast5_cbc			108
#define OBJ_cast5_cbc			1L,2L,840L,113533L,7L,66L,10L

#define SN_cast5_ecb			"CAST5-ECB"
#define LN_cast5_ecb			"cast5-ecb"
#define NID_cast5_ecb			109

#define SN_cast5_cfb64			"CAST5-CFB"
#define LN_cast5_cfb64			"cast5-cfb"
#define NID_cast5_cfb64			110

#define SN_cast5_ofb64			"CAST5-OFB"
#define LN_cast5_ofb64			"cast5-ofb"
#define NID_cast5_ofb64			111

#define LN_pbeWithMD5AndCast5_CBC	"pbeWithMD5AndCast5CBC"
#define NID_pbeWithMD5AndCast5_CBC	112
#define OBJ_pbeWithMD5AndCast5_CBC	1L,2L,840L,113533L,7L,66L,12L

/* This is one sun will soon be using :-(
 * id-dsa-with-sha1 ID  ::= {
 *   iso(1) member-body(2) us(840) x9-57 (10040) x9cm(4) 3 }
 */
#define SN_dsaWithSHA1			"DSA-SHA1"
#define LN_dsaWithSHA1			"dsaWithSHA1"
#define NID_dsaWithSHA1			113
#define OBJ_dsaWithSHA1			1L,2L,840L,10040L,4L,3L

#define NID_md5_sha1			114
#define SN_md5_sha1			"MD5-SHA1"
#define LN_md5_sha1			"md5-sha1"

#define SN_sha1WithRSA			"RSA-SHA1-2"
#define LN_sha1WithRSA			"sha1WithRSA"
#define NID_sha1WithRSA			115
#define OBJ_sha1WithRSA			OBJ_algorithm,29L

#define SN_dsa				"DSA"
#define LN_dsa				"dsaEncryption"
#define NID_dsa				116
#define OBJ_dsa				1L,2L,840L,10040L,4L,1L

#define SN_ripemd160			"RIPEMD160"
#define LN_ripemd160			"ripemd160"
#define NID_ripemd160			117
#define OBJ_ripemd160			1L,3L,36L,3L,2L,1L

/* The name should actually be rsaSignatureWithripemd160, but I'm going
 * to continue using the convention I'm using with the other ciphers */
#define SN_ripemd160WithRSA		"RSA-RIPEMD160"
#define LN_ripemd160WithRSA		"ripemd160WithRSA"
#define NID_ripemd160WithRSA		119
#define OBJ_ripemd160WithRSA		1L,3L,36L,3L,3L,1L,2L

/* Taken from rfc2040
 *  RC5_CBC_Parameters ::= SEQUENCE {
 *	version           INTEGER (v1_0(16)),
 *	rounds            INTEGER (8..127),
 *	blockSizeInBits   INTEGER (64, 128),
 *	iv                OCTET STRING OPTIONAL
 *	}
 */
#define SN_rc5_cbc			"RC5-CBC"
#define LN_rc5_cbc			"rc5-cbc"
#define NID_rc5_cbc			120
#define OBJ_rc5_cbc			OBJ_rsadsi,3L,8L

#define SN_rc5_ecb			"RC5-ECB"
#define LN_rc5_ecb			"rc5-ecb"
#define NID_rc5_ecb			121

#define SN_rc5_cfb64			"RC5-CFB"
#define LN_rc5_cfb64			"rc5-cfb"
#define NID_rc5_cfb64			122

#define SN_rc5_ofb64			"RC5-OFB"
#define LN_rc5_ofb64			"rc5-ofb"
#define NID_rc5_ofb64			123

#define SN_rle_compression		"RLE"
#define LN_rle_compression		"run length compression"
#define NID_rle_compression		124
#define OBJ_rle_compression		1L,1L,1L,1L,666L,1L

#define SN_zlib_compression		"ZLIB"
#define LN_zlib_compression		"zlib compression"
#define NID_zlib_compression		125
#define OBJ_zlib_compression		1L,1L,1L,1L,666L,2L

#define SN_ext_key_usage		"extendedKeyUsage"
#define LN_ext_key_usage		"X509v3 Extended Key Usage"
#define NID_ext_key_usage		126
#define OBJ_ext_key_usage		OBJ_id_ce,37

#define SN_id_pkix			"PKIX"
#define NID_id_pkix			127
#define OBJ_id_pkix			1L,3L,6L,1L,5L,5L,7L

#define SN_id_kp			"id-kp"
#define NID_id_kp			128
#define OBJ_id_kp			OBJ_id_pkix,3L

/* PKIX extended key usage OIDs */

#define SN_server_auth			"serverAuth"
#define LN_server_auth			"TLS Web Server Authentication"
#define NID_server_auth			129
#define OBJ_server_auth			OBJ_id_kp,1L

#define SN_client_auth			"clientAuth"
#define LN_client_auth			"TLS Web Client Authentication"
#define NID_client_auth			130
#define OBJ_client_auth			OBJ_id_kp,2L

#define SN_code_sign			"codeSigning"
#define LN_code_sign			"Code Signing"
#define NID_code_sign			131
#define OBJ_code_sign			OBJ_id_kp,3L

#define SN_email_protect		"emailProtection"
#define LN_email_protect		"E-mail Protection"
#define NID_email_protect		132
#define OBJ_email_protect		OBJ_id_kp,4L

#define SN_time_stamp			"timeStamping"
#define LN_time_stamp			"Time Stamping"
#define NID_time_stamp			133
#define OBJ_time_stamp			OBJ_id_kp,8L

/* Additional extended key usage OIDs: Microsoft */

#define SN_ms_code_ind			"msCodeInd"
#define LN_ms_code_ind			"Microsoft Individual Code Signing"
#define NID_ms_code_ind			134
#define OBJ_ms_code_ind			1L,3L,6L,1L,4L,1L,311L,2L,1L,21L

#define SN_ms_code_com			"msCodeCom"
#define LN_ms_code_com			"Microsoft Commercial Code Signing"
#define NID_ms_code_com			135
#define OBJ_ms_code_com			1L,3L,6L,1L,4L,1L,311L,2L,1L,22L

#define SN_ms_ctl_sign			"msCTLSign"
#define LN_ms_ctl_sign			"Microsoft Trust List Signing"
#define NID_ms_ctl_sign			136
#define OBJ_ms_ctl_sign			1L,3L,6L,1L,4L,1L,311L,10L,3L,1L

#define SN_ms_sgc			"msSGC"
#define LN_ms_sgc			"Microsoft Server Gated Crypto"
#define NID_ms_sgc			137
#define OBJ_ms_sgc			1L,3L,6L,1L,4L,1L,311L,10L,3L,3L

#define SN_ms_efs			"msEFS"
#define LN_ms_efs			"Microsoft Encrypted File System"
#define NID_ms_efs			138
#define OBJ_ms_efs			1L,3L,6L,1L,4L,1L,311L,10L,3L,4L

/* Additional usage: Netscape */

#define SN_ns_sgc			"nsSGC"
#define LN_ns_sgc			"Netscape Server Gated Crypto"
#define NID_ns_sgc			139
#define OBJ_ns_sgc			OBJ_netscape,4L,1L

#define SN_delta_crl			"deltaCRL"
#define LN_delta_crl			"X509v3 Delta CRL Indicator"
#define NID_delta_crl			140
#define OBJ_delta_crl			OBJ_id_ce,27L

#define SN_crl_reason			"CRLReason"
#define LN_crl_reason			"CRL Reason Code"
#define NID_crl_reason			141
#define OBJ_crl_reason			OBJ_id_ce,21L

#define SN_invalidity_date		"invalidityDate"
#define LN_invalidity_date		"Invalidity Date"
#define NID_invalidity_date		142
#define OBJ_invalidity_date		OBJ_id_ce,24L

#define SN_sxnet			"SXNetID"
#define LN_sxnet			"Strong Extranet ID"
#define NID_sxnet			143
#define OBJ_sxnet			1L,3L,101L,1L,4L,1L

/* PKCS12 and related OBJECT IDENTIFIERS */

#define OBJ_pkcs12			OBJ_pkcs,12L
#define OBJ_pkcs12_pbeids		OBJ_pkcs12, 1

#define SN_pbe_WithSHA1And128BitRC4	"PBE-SHA1-RC4-128"
#define LN_pbe_WithSHA1And128BitRC4	"pbeWithSHA1And128BitRC4"
#define NID_pbe_WithSHA1And128BitRC4	144
#define OBJ_pbe_WithSHA1And128BitRC4	OBJ_pkcs12_pbeids, 1L

#define SN_pbe_WithSHA1And40BitRC4	"PBE-SHA1-RC4-40"
#define LN_pbe_WithSHA1And40BitRC4	"pbeWithSHA1And40BitRC4"
#define NID_pbe_WithSHA1And40BitRC4	145
#define OBJ_pbe_WithSHA1And40BitRC4	OBJ_pkcs12_pbeids, 2L

#define SN_pbe_WithSHA1And3_Key_TripleDES_CBC	"PBE-SHA1-3DES"
#define LN_pbe_WithSHA1And3_Key_TripleDES_CBC	"pbeWithSHA1And3-KeyTripleDES-CBC"
#define NID_pbe_WithSHA1And3_Key_TripleDES_CBC	146
#define OBJ_pbe_WithSHA1And3_Key_TripleDES_CBC	OBJ_pkcs12_pbeids, 3L

#define SN_pbe_WithSHA1And2_Key_TripleDES_CBC	"PBE-SHA1-2DES"
#define LN_pbe_WithSHA1And2_Key_TripleDES_CBC	"pbeWithSHA1And2-KeyTripleDES-CBC"
#define NID_pbe_WithSHA1And2_Key_TripleDES_CBC	147
#define OBJ_pbe_WithSHA1And2_Key_TripleDES_CBC	OBJ_pkcs12_pbeids, 4L

#define SN_pbe_WithSHA1And128BitRC2_CBC		"PBE-SHA1-RC2-128"
#define LN_pbe_WithSHA1And128BitRC2_CBC		"pbeWithSHA1And128BitRC2-CBC"
#define NID_pbe_WithSHA1And128BitRC2_CBC	148
#define OBJ_pbe_WithSHA1And128BitRC2_CBC	OBJ_pkcs12_pbeids, 5L

#define SN_pbe_WithSHA1And40BitRC2_CBC	"PBE-SHA1-RC2-40"
#define LN_pbe_WithSHA1And40BitRC2_CBC	"pbeWithSHA1And40BitRC2-CBC"
#define NID_pbe_WithSHA1And40BitRC2_CBC	149
#define OBJ_pbe_WithSHA1And40BitRC2_CBC	OBJ_pkcs12_pbeids, 6L

#define OBJ_pkcs12_Version1	OBJ_pkcs12, 10L

#define OBJ_pkcs12_BagIds	OBJ_pkcs12_Version1, 1L

#define LN_keyBag		"keyBag"
#define NID_keyBag		150
#define OBJ_keyBag		OBJ_pkcs12_BagIds, 1L

#define LN_pkcs8ShroudedKeyBag	"pkcs8ShroudedKeyBag"
#define NID_pkcs8ShroudedKeyBag	151
#define OBJ_pkcs8ShroudedKeyBag	OBJ_pkcs12_BagIds, 2L

#define LN_certBag		"certBag"
#define NID_certBag		152
#define OBJ_certBag		OBJ_pkcs12_BagIds, 3L

#define LN_crlBag		"crlBag"
#define NID_crlBag		153
#define OBJ_crlBag		OBJ_pkcs12_BagIds, 4L

#define LN_secretBag		"secretBag"
#define NID_secretBag		154
#define OBJ_secretBag		OBJ_pkcs12_BagIds, 5L

#define LN_safeContentsBag	"safeContentsBag"
#define NID_safeContentsBag	155
#define OBJ_safeContentsBag	OBJ_pkcs12_BagIds, 6L

#define LN_friendlyName		"friendlyName"
#define	NID_friendlyName	156
#define OBJ_friendlyName	OBJ_pkcs9, 20L

#define LN_localKeyID		"localKeyID"
#define	NID_localKeyID		157
#define OBJ_localKeyID		OBJ_pkcs9, 21L

#define OBJ_certTypes		OBJ_pkcs9, 22L

#define LN_x509Certificate	"x509Certificate"
#define	NID_x509Certificate	158
#define OBJ_x509Certificate	OBJ_certTypes, 1L

#define LN_sdsiCertificate	"sdsiCertificate"
#define	NID_sdsiCertificate	159
#define OBJ_sdsiCertificate	OBJ_certTypes, 2L

#define OBJ_crlTypes		OBJ_pkcs9, 23L

#define LN_x509Crl		"x509Crl"
#define	NID_x509Crl		160
#define OBJ_x509Crl		OBJ_crlTypes, 1L

/* PKCS#5 v2 OIDs */

#define LN_pbes2		"PBES2"
#define NID_pbes2		161
#define OBJ_pbes2		OBJ_pkcs,5L,13L

#define LN_pbmac1		"PBMAC1"
#define NID_pbmac1		162
#define OBJ_pbmac1		OBJ_pkcs,5L,14L

#define LN_hmacWithSHA1		"hmacWithSHA1"
#define NID_hmacWithSHA1	163
#define OBJ_hmacWithSHA1	OBJ_rsadsi,2L,7L

/* Policy Qualifier Ids */

#define LN_id_qt_cps		"Policy Qualifier CPS"
#define SN_id_qt_cps		"id-qt-cps"
#define NID_id_qt_cps		164
#define OBJ_id_qt_cps		OBJ_id_pkix,2L,1L

#define LN_id_qt_unotice	"Policy Qualifier User Notice"
#define SN_id_qt_unotice	"id-qt-unotice"
#define NID_id_qt_unotice	165
#define OBJ_id_qt_unotice	OBJ_id_pkix,2L,2L

#define SN_rc2_64_cbc			"RC2-64-CBC"
#define LN_rc2_64_cbc			"rc2-64-cbc"
#define NID_rc2_64_cbc			166

#define SN_SMIMECapabilities		"SMIME-CAPS"
#define LN_SMIMECapabilities		"S/MIME Capabilities"
#define NID_SMIMECapabilities		167
#define OBJ_SMIMECapabilities		OBJ_pkcs9,15L

#define SN_pbeWithMD2AndRC2_CBC		"PBE-MD2-RC2-64"
#define LN_pbeWithMD2AndRC2_CBC		"pbeWithMD2AndRC2-CBC"
#define NID_pbeWithMD2AndRC2_CBC	168
#define OBJ_pbeWithMD2AndRC2_CBC	OBJ_pkcs,5L,4L

#define SN_pbeWithMD5AndRC2_CBC		"PBE-MD5-RC2-64"
#define LN_pbeWithMD5AndRC2_CBC		"pbeWithMD5AndRC2-CBC"
#define NID_pbeWithMD5AndRC2_CBC	169
#define OBJ_pbeWithMD5AndRC2_CBC	OBJ_pkcs,5L,6L

#define SN_pbeWithSHA1AndDES_CBC	"PBE-SHA1-DES"
#define LN_pbeWithSHA1AndDES_CBC	"pbeWithSHA1AndDES-CBC"
#define NID_pbeWithSHA1AndDES_CBC	170
#define OBJ_pbeWithSHA1AndDES_CBC	OBJ_pkcs,5L,10L

/* Extension request OIDs */

#define LN_ms_ext_req			"Microsoft Extension Request"
#define SN_ms_ext_req			"msExtReq"
#define NID_ms_ext_req			171
#define OBJ_ms_ext_req			1L,3L,6L,1L,4L,1L,311L,2L,1L,14L

#define LN_ext_req			"Extension Request"
#define SN_ext_req			"extReq"
#define NID_ext_req			172
#define OBJ_ext_req			OBJ_pkcs9,14L

#define SN_name				"name"
#define LN_name				"name"
#define NID_name			173
#define OBJ_name			OBJ_X509,41L

#define SN_dnQualifier			"dnQualifier"
#define LN_dnQualifier			"dnQualifier"
#define NID_dnQualifier			174
#define OBJ_dnQualifier			OBJ_X509,46L

#define SN_id_pe			"id-pe"
#define NID_id_pe			175
#define OBJ_id_pe			OBJ_id_pkix,1L

#define SN_id_ad			"id-ad"
#define NID_id_ad			176
#define OBJ_id_ad			OBJ_id_pkix,48L

#define SN_info_access			"authorityInfoAccess"
#define LN_info_access			"Authority Information Access"
#define NID_info_access			177
#define OBJ_info_access			OBJ_id_pe,1L

#define SN_ad_OCSP			"OCSP"
#define LN_ad_OCSP			"OCSP"
#define NID_ad_OCSP			178
#define OBJ_ad_OCSP			OBJ_id_ad,1L

#define SN_ad_ca_issuers		"caIssuers"
#define LN_ad_ca_issuers		"CA Issuers"
#define NID_ad_ca_issuers		179
#define OBJ_ad_ca_issuers		OBJ_id_ad,2L

#define SN_OCSP_sign			"OCSPSigning"
#define LN_OCSP_sign			"OCSP Signing"
#define NID_OCSP_sign			180
#define OBJ_OCSP_sign			OBJ_id_kp,9L

#define OBJ_csor		2L,16L,840L,1L,101L,3L

#define OBJ_nistAlgorithms		OBJ_csor,4L

#define OBJ_aes		OBJ_nistAlgorithms,1L

#define SN_aes_128_ecb		"AES-128-ECB"
#define LN_aes_128_ecb		"aes-128-ecb"
#define NID_aes_128_ecb		418
#define OBJ_aes_128_ecb		OBJ_aes,1L

#define SN_aes_128_cbc		"AES-128-CBC"
#define LN_aes_128_cbc		"aes-128-cbc"
#define NID_aes_128_cbc		419
#define OBJ_aes_128_cbc		OBJ_aes,2L

#define SN_aes_128_ofb128		"AES-128-OFB"
#define LN_aes_128_ofb128		"aes-128-ofb"
#define NID_aes_128_ofb128		420
#define OBJ_aes_128_ofb128		OBJ_aes,3L

#define SN_aes_128_cfb128		"AES-128-CFB"
#define LN_aes_128_cfb128		"aes-128-cfb"
#define NID_aes_128_cfb128		421
#define OBJ_aes_128_cfb128		OBJ_aes,4L

#define SN_aes_192_ecb		"AES-192-ECB"
#define LN_aes_192_ecb		"aes-192-ecb"
#define NID_aes_192_ecb		422
#define OBJ_aes_192_ecb		OBJ_aes,21L

#define SN_aes_192_cbc		"AES-192-CBC"
#define LN_aes_192_cbc		"aes-192-cbc"
#define NID_aes_192_cbc		423
#define OBJ_aes_192_cbc		OBJ_aes,22L

#define SN_aes_192_ofb128		"AES-192-OFB"
#define LN_aes_192_ofb128		"aes-192-ofb"
#define NID_aes_192_ofb128		424
#define OBJ_aes_192_ofb128		OBJ_aes,23L

#define SN_aes_192_cfb128		"AES-192-CFB"
#define LN_aes_192_cfb128		"aes-192-cfb"
#define NID_aes_192_cfb128		425
#define OBJ_aes_192_cfb128		OBJ_aes,24L

#define SN_aes_256_ecb		"AES-256-ECB"
#define LN_aes_256_ecb		"aes-256-ecb"
#define NID_aes_256_ecb		426
#define OBJ_aes_256_ecb		OBJ_aes,41L

#define SN_aes_256_cbc		"AES-256-CBC"
#define LN_aes_256_cbc		"aes-256-cbc"
#define NID_aes_256_cbc		427
#define OBJ_aes_256_cbc		OBJ_aes,42L

#define SN_aes_256_ofb128		"AES-256-OFB"
#define LN_aes_256_ofb128		"aes-256-ofb"
#define NID_aes_256_ofb128		428
#define OBJ_aes_256_ofb128		OBJ_aes,43L

#define SN_aes_256_cfb128		"AES-256-CFB"
#define LN_aes_256_cfb128		"aes-256-cfb"
#define NID_aes_256_cfb128		429
#define OBJ_aes_256_cfb128		OBJ_aes,44L

#define SN_aes_128_cfb1		"AES-128-CFB1"
#define LN_aes_128_cfb1		"aes-128-cfb1"
#define NID_aes_128_cfb1		650

#define SN_aes_192_cfb1		"AES-192-CFB1"
#define LN_aes_192_cfb1		"aes-192-cfb1"
#define NID_aes_192_cfb1		651

#define SN_aes_256_cfb1		"AES-256-CFB1"
#define LN_aes_256_cfb1		"aes-256-cfb1"
#define NID_aes_256_cfb1		652

#define SN_aes_128_cfb8		"AES-128-CFB8"
#define LN_aes_128_cfb8		"aes-128-cfb8"
#define NID_aes_128_cfb8		653

#define SN_aes_192_cfb8		"AES-192-CFB8"
#define LN_aes_192_cfb8		"aes-192-cfb8"
#define NID_aes_192_cfb8		654

#define SN_aes_256_cfb8		"AES-256-CFB8"
#define LN_aes_256_cfb8		"aes-256-cfb8"
#define NID_aes_256_cfb8		655

#endif		// #ifndef NID_undef
/**
\endcond */


// X509 information type define
#define X509_VERSION                    0		/*!< Get version of certificate */
#define X509_NOTBEFORE                  1		/*!< Get beginning validity date of certificate */
#define X509_NOTAFTER                   2		/*!< Get end validity date of certificate */
#define X509_SIGTYPE                    3		/*!< Get signature type of certificate*/
#define X509_PUBKEYALGO                 4		/*!< Get public key algorithm of certificate */
#define X509_PUBKEYSTRENGTH             5		/*!< Get public key strength of certificate */
#define X509_ISSUER                     6		/*!< Get issuer information of certificate by NID */
#define X509_SUBJECT                    7		/*!< Get subject information of certificate by NID */
#define X509_SERIAL                     8		/*!< Get serial number of certificate */
#define X509_EXTENSIONS                 9		/*!< Get X509 extension of certificate by NID */
#define X509_ISSUER_BY_OID				10		/*!< Get issuer information of certificate by OID*/
#define X509_SUBJECT_BY_OID				11		/*!< Get subject information of certificate by OID */
#define X509_EXTENSIONS_BY_OID			12		/*!< Get X509 extension of certificate by OID */

// X509 CRL information type define
#define X509_CRL_VERSION				0		/*!< Get version of CRL */
#define X509_CRL_LASTUPDATE				1		/*!< Get beginning validity date of CRL */
#define X509_CRL_NEXTUPDATE				2		/*!< Get end validity date of CRL */
#define X509_CRL_ISSUER					6		/*!< Get issuer information of CRL by NID */

// PKCS12 error define
#define SSL_PKCS12_EOK                  0		/*!< Ok (no error)*/
#define SSL_PKCS12_EKO                  -1		/*!< Error*/
#define SSL_PKCS12_EBADPASSWORD         -2		/*!< Bad password*/
#define SSL_PKCS12_EBADFORMAT           -3		/*!< Bad format of pksc12 file*/
#define SSL_PKCS12_ENOMORECA            -4		/*!< No CA in PKCS12*/

// Hash algorithm

//! \defgroup HASH_ALGO Hash algorithms
//! \brief Hash algorithms
//! Refer fuction \ref calculate_hash().
//! @{
#define HASH_ALGO_SHA1 					1		/*!< SHA-1*/
#define HASH_ALGO_SHA256				2		/*!< SHA-256*/
#define HASH_ALGO_SHA384				3		/*!< SHA-384*/
#define HASH_ALGO_SHA512				4		/*!< SHA-512*/
// -- DO NOT SUPPRESS THIS LINE -------------------
//! @}

/*
======================================================================
                        Data Structures Definition
======================================================================
*/

/*! @brief Information to add to a certificate request */
typedef struct csr_option_st CsrOption;
struct csr_option_st
{
        int nid;                        /*!< Identification number (NID_xxxxxx) */
        char * szValue;                 /*!< Value */
};


#ifndef __SSL_HANDLES__
typedef void * SSL_HANDLE;              /*!< SSL session handle */
typedef void * SSL_SERVER_HANDLE;       /*!< SSL server handle */
typedef void * SSL_PROFILE_HANDLE;      /*!< SSL profile handle */
typedef void * X509_HANDLE;             /*!< X509 certificate handle */
typedef void * X509_CRL_HANDLE;         /*!< X509 CRL handle */
#define __SSL_HANDLES__
#endif

/*
======================================================================
                        Functions Definition
======================================================================
*/

/*! @brief This function opens a CA or a certificate file and return a handle
 * @param fileName	: The CA or certificate file name
 * @return The handle of the loaded certificate
 *
 *	@link KSFAM_X509 Back to top @endlink
 **/
X509_HANDLE X509_Load( const char *fileName );


/*! @brief This function copies the peer certificate of an SSL session and return a handle
 * @param ssl : A SSL structure handle
 * @return The handle of the peer certificate or NULL. If this handle is not NULL, and once it is no more used
 * by the application, it must be released using \ref X509_Unload.
 *
 *	@link KSFAM_X509 Back to top @endlink
 **/
X509_HANDLE X509_GetPeerCertificate(SSL_HANDLE ssl);


/*! @brief This function deletes a loaded certificate
 * @param x509 : x509 certificate handle
 * @return OK (0) if successful, otherwise negative error code
 *
 *	@link KSFAM_X509 Back to top @endlink
 **/
int X509_Unload( X509_HANDLE x509 );


/*! @brief This function retrieves a specific information or field contained in a certificate or ca
 * @param x509	: A handle on a loaded certificate
 * @param informationType	: The information type (X509_VERSION, X509_NOTBEFORE, ...)
 * @param field	: The 'nid'value for X509_ISSUER, X509_SUBJECT or X509_EXTENSIONS information type
 * @param buffer	: The buffer where result is stored. Must contain in input the string of the oid if informationType is set to X509_ISSUER_BY_OID, X509_SUBJECT_BY_OID or X509_EXTENSIONS_BY_OID.
 * @param buflen	: The size of the buffer
 * @return The size of data in the buffer if successful, otherwise negative error code
 *
 *	@link KSFAM_X509 Back to top @endlink
 **/
int X509_GetInfo(X509_HANDLE x509, int informationType, int field, char * buffer, int buflen);


/*! @brief Verification signature chain of a certificate
 * @param ca: A list of handle on loaded trusted certificates
 * @param nb_ca: Number of element in the ca list
 * @param cert: A handle on loaded certificate to check
 * @return: 0 if successful, otherwise error code
 *
 *	@link KSFAM_X509 Back to top @endlink
 */
int X509_VerifyCertificate(X509_HANDLE * ca, unsigned int nb_ca, X509_HANDLE cert);


/*! @brief Get RSA public key of a certificate
 * @param cert: A handle on a loaded certificate
 * @param rsa_modulus: Buffer where the modulus must be stored in big endian
 * @param rsa_modulus_length: Length of stored data in rsa_modulus buffer
 * @param rsa_exponent: Buffer where the public exponent must be stored in big endian
 * @param  rsa_exponent_length: Length of stored data in rsa_modulus buffer
 * @return: 0 if successful, otherwise negative error code
 *
 *	@link KSFAM_X509 Back to top @endlink
 */
int X509_GetRsaPublicKey(X509_HANDLE cert, unsigned char * rsa_modulus, unsigned int * rsa_modulus_length, unsigned char * rsa_exponent, unsigned int * rsa_exponent_length);


/*! @brief This function checks that a certificate and a private key match
 *
 *	The parameter 'isEncrypted' indicates if the key file is encrypted. It is the
                case when the keys are automatically generated by the terminal
 *
 * @param certificateFile	: Certificate file
 * @param keyFile	: Private key file
 * @param isEncrypted	: TRUE if the private key is encrypted with internal key, otherwise FALSE
 * @return : 0 if successful, otherwise error code
 *
 * @link KSFAM_X509 Back to top @endlink 
**/
int X509_CheckPrivateKey( const char * certificateFile, const char * keyFile, int isEncrypted);


/*! @brief This function crypts an RSA key with the DLL SSL internal key
 * @param key : The buffer with the RSA key (X509 - PEM format) protected or not by a password
 * @param keylen : The size of the key buffer
 * @param password : The password of RSA key. Must be NULL if RSA key file doesn't have password
 * @param crypt : The buffer where the result is stored
 * @param cryptlen : The size of the result buffer
 * @return The size of data in the buffer if successful, otherwise negative error code (SSL_RSA_ENOK, SSL_RSA_ENOKEY)
 *
 * @link KSFAM_X509 Back to top @endlink
 **/
int X509_RsaKeyCrypt(const char * key, int keylen,const char * password, char * crypt, int cryptlen);


/*! @brief This function generates an encrypted RSA key and stores it in a buffer.
 * 
 * @brief The enciphering key is internally protected in the cryptographic unit.
 * @param bits	: The size in bit of the RSA key
 * @param e	: The exponent (odd number) use in RSA generation (e.g.:3,17,65537)
 * @param buffer	:	The buffer where result is stored
 * @param buflen	: The size of the buffer
 * @return The size of data in the buffer if successful, otherwise negative error code
 *				(#SSL_RSA_ENOK)
 *
 *	@link KSFAM_X509 Back to top @endlink
 **/
int rsaKeyGen(int bits, unsigned long e,char * buffer,int buflen);


/*! @brief This function generates a Certificate Signature Request (CSR) and writes it in a buffer
 * @param keyFile	: RSA key file name
 * @param options : List of options to add in the CSR
 * @param nb_options	: Size of the "options" table
 * @param buf	: The buffer where result is stored
 * @param len	: The size of the buffer
 * @return The size of data in the buffer if successful, otherwise negative error code
 *				(#SSL_RSA_ENOK, #SSL_RSA_ENOKEY)
 *
 *	@link KSFAM_X509 Back to top @endlink
 **/
int rsaCsrGen(const char * keyFile, CsrOption * options, int nb_options, void * buf, int len );


/*! @brief This function crypts an RSA key
 * @param key	: The buffer with the RSA key
 * @param keylen	: The size of the key buffer
 * @param crypt	: The buffer where the result is stored
 * @param cryptlen	: The size of the result buffer
 * @return The size of data in the buffer if successful, otherwise negative error code (SSL_RSA_ENOK, SSL_RSA_ENOKEY)
 *
 *	@link KSFAM_X509 Back to top @endlink
 **/
int rsaKeyCrypt(const char * key,int keylen,char * crypt,int cryptlen);


/*! @brief Calculate a hash on a data buffer
 * @param hash_type	: \ref HASH_ALGO
 * @param data	: Data buffer
 * @param data_length	: Length of the data buffer
 * @param digest	: Result buffer where the hash value must be stored (the maximum size of the buffer is 64 for #HASH_ALGO_SHA512)
 * @return The size of data in the result buffer if successful, otherwise negative error code (#SSL_EINVAL)
 *
 *	@link KSFAM_X509 Back to top @endlink
 **/
int calculate_hash(unsigned int hash_type, unsigned char * data, unsigned int data_length, unsigned char * digest);


/*! @brief This function extracts an RSA key from a PKCS12 encrypted file
 * @param pkcs12File	: The name of the PKCS12 file which contains the RSA key to extract
 * @param password	: Password string for PKCS12 file
 * @param buffer	: The buffer where extracted key is stored.  Must be allocated by the caller part.
 * @param buflen	: The size of the buffer
 * @return The size of data in the buffer if successful, otherwise negative error code
 *				(#SSL_PKCS12_EKO, #SSL_PKCS12_EBADPASSWORD, #SSL_PKCS12_EBADFORMAT)
 *
 *	@link KSFAM_X509 Back to top @endlink
 **/
int PKCS12_GetPrivateKey(const char * pkcs12File, const char * password, char * buffer, int buflen);


/*! @brief This function reads the certificate key of a PKCS12
 * @param pkcs12File	: PKCS12 file name
 * @param password	: Password string for PKCS12 file
 * @param buffer	: The buffer where result is stored
 * @param buflen	: The size of the buffer
 * @return The size of data in the buffer if successful, otherwise negative error code
 *				(#SSL_PKCS12_EKO, #SSL_PKCS12_EBADPASSWORD, #SSL_PKCS12_EBADFORMAT)
 *
 *	@link KSFAM_X509 Back to top @endlink
 **/
int PKCS12_GetCertificate(const char * pkcs12File, const char * password, char * buffer, int buflen);


/*! @brief This function reads a CA of a PKCS12.
 * 
 * @brief The certificate is searched according to its index in the file. 
                When the given index is invalid, the function returns the error: #SSL_PKCS12_ENOMORECA
 * @param pkcs12File	: PKCS12 file name
 * @param password	: Password string for PKCS12 file
 * @param num	: The number of CA (0 to n)
 * @param buffer	: The buffer where result is stored
 * @param buflen	: The size of the buffer
 * @return The size of data in the buffer if successful, otherwise negative error code
 *				(#SSL_PKCS12_EKO, #SSL_PKCS12_EBADPASSWORD, #SSL_PKCS12_EBADFORMAT, #SSL_PKCS12_ENOMORECA)
 *
 *	@link KSFAM_X509 Back to top @endlink
 **/
int PKCS12_GetCA(const char * pkcs12File, const char * password, int num, char * buffer, int buflen);


/*! @brief This function opens a CRL file and return a handle
 * @param fileName	: The CRL file name
 * @return The handle of the loaded CRL
 *
 *	@link KSFAM_X509 Back to top @endlink
 **/
X509_CRL_HANDLE X509_CrlLoad( const char *fileName );


/*! @brief This function deletes a loaded CRL
 * @param x509 : x509 CRL handle
 * @return OK (0) if successful, otherwise negative error code
 *
 *	@link KSFAM_X509 Back to top @endlink
 **/
int X509_CrlUnload(X509_CRL_HANDLE x509);


/*! @brief This function retrieves a specific information or field contained in a CRL
 * @param x509	: A handle on a loaded CRL
 * @param informationType	: The information type (X509_CRL_VERSION, X509_CRL_LASTUPDATE, ...)
 * @param field	: The 'nid'value for X509_CRL_ISSUER information type
 * @param buffer	: The buffer where result is stored. Must contain in input the string of the oid if informationType is set to X509_ISSUER_BY_OID, X509_SUBJECT_BY_OID or X509_EXTENSIONS_BY_OID.
 * @param buflen	: The size of the buffer
 * @return The size of data in the buffer if successful, otherwise negative error code
 *
 *	@link KSFAM_X509 Back to top @endlink
 **/
int X509_CrlGetInfo(X509_CRL_HANDLE x509, int informationType, int field, char * buffer, int buflen);


#endif // __PACKSSL_COMPONENT_X509__
/*! @} **/

/*! @defgroup PKI_SAMPLES PKI management samples
 @ingroup TCPIP_SAMPLES
 PKI management functions (X509 certificates, RSA key generation...).  
 @{

		\defgroup SSL_PKI_PROF		Print the information about profiles.
		\ingroup PKI_SAMPLES
        * The sample code is adapted from the sample provided in the package.
        * It lists out all the profiles and print for each profile :
        * - its name, 
        * - the address of the last called server,
        * - the result of the last connection, 
        * - the client certificate
        * - and the all the CA certificates.
		*
        * For each certificate, it displays the validity dates.
//! \include X509__Sample_01.c
//! \example X509__Sample_01.c
		* @{
		* @}
 		\defgroup SSL_PKI_KEY_CSR		Key Handling and Certificate Request Generation.
		\ingroup PKI_SAMPLES
		* The sample below shows how to generate a SSL profile key and a certificate signature request.
//! \include X509__Sample_02.c
//! \example X509__Sample_02.c
		* @{
		* @}
		
		\defgroup SSL_PKI_PKCS12		Create a profile from a PKCS 12 archive file.
		\ingroup PKI_SAMPLES
		* This sample code shows how to create a profile from a PKCS12 archive file.
		* The privated key is extracted from the archive and stored in an encrypted file.
		* Then, a new profile is created containing all the certificates located in the
		* archive.
		*
		*
		* <b>Notes</b>: 
		* - Be careful about the size of the filenames and about their case (with LLT, the names of 
		* the downloaded file are always uppercase).
		* - The command to generate a PKCS12 file using OpenSSL is "openssl pkcs12 -in cert.crt -inkey key.pem -noout -export > pkcs12.p12".
		* 
		*
//! \include X509__Sample_03.c
//! \example X509__Sample_03.c
		* @{
		* @}
@} **/
