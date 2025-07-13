package com.ingenico.tml.example.toolkit;

import java.lang.reflect.Method;
import java.text.DateFormat;
import java.text.ParseException;
import java.text.SimpleDateFormat;
import java.util.Calendar;
import java.util.Date;
import java.util.GregorianCalendar;
import java.util.HashMap;
import java.util.Map;
import java.util.TimeZone;

import org.apache.commons.codec.binary.Base64;

/**
 * This class represents set of utils
 * @author Eugene Pestov
 */
public class Utils {

    /**
     * maps of converters
     */
    private static HashMap<String, Converter> convertersMap = new HashMap<String, Converter>();

    /**
     * initialises converter maps
     */
    static {
        // String converter
        convertersMap.put("object", new Converter() {
            public Class getJavaType() {
                return Object.class;
            }

            public Object convert(String value) {
                return value;
            }
        });

        // String converter
        convertersMap.put("string", new Converter() {
            public Class getJavaType() {
                return String.class;
            }

            public Object convert(String value) {
                return value;
            }
        });
        // int converter
        convertersMap.put("integer", new Converter() {
            public Class getJavaType() {
                return int.class;
            }

            public Object convert(String value) throws TmlParseException {
                try {
                    return Integer.valueOf(value);
                } catch (NumberFormatException e) {
                    throw new TmlParseException(
                            "Could not parse integer data: " + e.getMessage());
                }
            }
        });

        // Date converter
        convertersMap.put("date", new Converter() {
            public Class getJavaType() {
                return Date.class;
            }

            public Object convert(String value) throws TmlParseException {
                if (value.trim().equals("")) {
                    value = "00 00 0000 00:00:00 GMT";
                }
                // date is represented in number of seconds since the epoch
                try {
                    DateFormat df = new SimpleDateFormat("dd MM yyyy HH:mm:ss zzz");
                    Date date = df.parse(value);
                    return date;
                } catch (ParseException e) {
                    throw new TmlParseException("Could not parse date: "
                            + e.getMessage());
                }
            }
        });

        // base64 to byte[] converter
        convertersMap.put("opaque", new Converter() {
            public Class getJavaType() {
                return byte[].class;
            }

            public Object convert(String value) throws TmlParseException {
                String base64value = value;
                try {
                    return Base64.decodeBase64(base64value.getBytes());
                } catch (Exception e) {
                    throw new TmlParseException("Could not parse opaque data: "
                            + e.getMessage());
                }
            }
        });
    }

    /**
     * Converter interface
     */
    private interface Converter {

        /**
         * Gets java type
         * @return java type
         */
        Class getJavaType();

        /**
         * Converts value
         * @param value value to convert
         * @return converted data
         * @throws TmlParseException in case of parsing error occurs
         */
        Object convert(String value) throws TmlParseException;
    }

    /**
     * This method tries to set property with name <code>name</code> for the
     * bean <code>dataObj</code>
     * 
     * @param dataObj tml post data
     * @param name property name
     * @param value property value
     * @throws TmlParseException in case of parsing error occurs
     */
    public static void setProperty(TmlPostData dataObj, String name,
            String type, String value) throws Exception {

        Class dataObjClass = dataObj.getClass();
        Map<String, String> fieldMappings = dataObj.getFieldMappings();
        // construct the setter name
        String fieldName = fieldMappings.get(name);
        if (fieldName != null) {
            String setterName = "set" + Character.toUpperCase(fieldName.charAt(0))
            + fieldName.substring(1);
            
            Converter conv;
            if (type != null)
                conv = convertersMap.get(type);
            else
                conv = convertersMap.get("object");
            
            if (conv == null) {
                throw new IllegalArgumentException("Unknown tml-variable type: "
                        + type);
            }

            // will try to locate an appropriate method
            Method method = dataObjClass.getMethod(setterName, new Class[] { conv
                    .getJavaType() });
            // create params for the method
            Object params[] = { conv.convert(value) };
            // invoke
            method.invoke(dataObj, params);
        }
        else {
            // Trying to call predefined setProperty() method
            Converter conv;
            if (type != null)
                conv = convertersMap.get(type);
            else
                conv = convertersMap.get("object");
            
            if (conv == null) {
                throw new IllegalArgumentException("Unknown tml-variable type: "
                        + type);
            }

            // will try to locate an appropriate method
            Method method = dataObjClass.getMethod("setField", new Class[] { String.class, conv.getJavaType() });
            // create params for the method
            Object params[] = { name, conv.convert(value) };
            // invoke
            method.invoke(dataObj, params);
        }
    }

    /**
     * Parses date
     * @param dateTimeStr datetime
     * @return parsed date
     */
    public static Date parseXSDateTime(String dateTimeStr) {
        boolean beforeChristmas = false;
        if (dateTimeStr == null) {
            throw new NumberFormatException("Null date/time string passed as parameter");
        }
        else if (dateTimeStr != null) {
            if (dateTimeStr.charAt(0) == '+')
                dateTimeStr = dateTimeStr.substring(1);

            if (dateTimeStr.charAt(0) == '-') {
                dateTimeStr = dateTimeStr.substring(1);
                beforeChristmas = true;
            }
        }

        if (dateTimeStr == null) {
            throw new NumberFormatException("Incorrect date/time format: " + dateTimeStr);
        }
        DateFormat df = new SimpleDateFormat("yyyy-MM-dd'T'HH:mm:ss");
        df.setTimeZone(TimeZone.getTimeZone("GMT"));
        Calendar calendar = Calendar.getInstance();
        Date date;
        // parse fixed portion of the format
        try {
            date = df.parse(dateTimeStr.substring(0, 19));
        } catch (ParseException e) {
            throw new NumberFormatException(e.toString());
        }

        int pos = 19;

        // parse optional milliseconds
        if (dateTimeStr != null) {
            if (pos < dateTimeStr.length() && dateTimeStr.charAt(pos) == '.') {
                int milliseconds = 0;
                int start = ++pos;
                while (pos < dateTimeStr.length()
                        && Character.isDigit(dateTimeStr.charAt(pos)))
                    pos++;

                String decimal = dateTimeStr.substring(start, pos);
                if (decimal.length() == 3) {
                    milliseconds = Integer.parseInt(decimal);
                } else if (decimal.length() < 3) {
                    milliseconds = Integer.parseInt((decimal + "000")
                            .substring(0, 3));
                } else {
                    milliseconds = Integer.parseInt(decimal.substring(0, 3));
                    if (decimal.charAt(3) >= '5')
                        ++milliseconds;
                }

                // add milliseconds to the current date
                date.setTime(date.getTime() + milliseconds);
            }

            // parse optional timezone
            if (pos + 5 < dateTimeStr.length()
                    && (dateTimeStr.charAt(pos) == '+' || (dateTimeStr
                            .charAt(pos) == '-'))) {
                if (!Character.isDigit(dateTimeStr.charAt(pos + 1))
                        || !Character.isDigit(dateTimeStr.charAt(pos + 2))
                        || dateTimeStr.charAt(pos + 3) != ':'
                        || !Character.isDigit(dateTimeStr.charAt(pos + 4))
                        || !Character.isDigit(dateTimeStr.charAt(pos + 5)))
                    throw new NumberFormatException("Bad time zone");

                int hours = (dateTimeStr.charAt(pos + 1) - '0') * 10
                        + dateTimeStr.charAt(pos + 2) - '0';
                int mins = (dateTimeStr.charAt(pos + 4) - '0') * 10
                        + dateTimeStr.charAt(pos + 5) - '0';
                int milliseconds = (hours * 60 + mins) * 60 * 1000;

                // subtract milliseconds from current date to obtain GMT
                if (dateTimeStr.charAt(pos) == '+')
                    milliseconds = -milliseconds;
                date.setTime(date.getTime() + milliseconds);
                pos += 6;
            }

            if (pos < dateTimeStr.length() && dateTimeStr.charAt(pos) == 'Z') {
                pos++;
                calendar.setTimeZone(TimeZone.getTimeZone("GMT"));
            }

            if (pos < dateTimeStr.length())
                throw new NumberFormatException("dateTime string is too long: "
                        + dateTimeStr);
        }

        calendar.setTime(date);

        // support dates before the Christian era
        if (beforeChristmas) {
            calendar.set(Calendar.ERA, GregorianCalendar.BC);
        }

        return date;
    }

    /**
     * Formats datetime
     * @param date datetime
     * @return formatted date
     */
    public static String formatXSDateTime(Date date) {
        DateFormat df = new SimpleDateFormat("yyyy-MM-dd'T'HH:mm:ss.SSS'Z'");
        df.setTimeZone(TimeZone.getTimeZone("GMT"));
        return df.format(date);
    }

    /**
     * Encodes to base64
     * @param binary binary data
     * @return encoded data
     */
    public static String encodeBase64(byte[] binary) {
        return binary != null ? new String(Base64.encodeBase64(binary)) : null;
    }

}
/*
 * Incendo Online TML Toolkit
 *
 * COPYRIGHT (C) 2003-2012 INGENICO ALL RIGHTS RESERVED
 *
 * Copyright in the whole and every part of this software program belongs to
 * Ingenico. It may not be used, sold, licensed, transferred, copied
 * or reproduced in whole or in part in any manner or form other than in
 * accordance with and subject to the terms of a licence from Ingenico
 * or with the prior written consent of Ingenico or as permitted by
 * applicable law.
 * This software program contains confidential and proprietary information and
 * must not be disclosed, in whole or in part, to any person or organisation
 * without the prior written consent of Ingenico.
 * Any copies or reproductions of this software program (in whole or in part)
 * made by any method must also include a copy of this legend.
 */