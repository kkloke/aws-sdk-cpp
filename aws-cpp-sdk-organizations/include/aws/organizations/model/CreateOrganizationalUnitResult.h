﻿/*
* Copyright 2010-2016 Amazon.com, Inc. or its affiliates. All Rights Reserved.
*
* Licensed under the Apache License, Version 2.0 (the "License").
* You may not use this file except in compliance with the License.
* A copy of the License is located at
*
*  http://aws.amazon.com/apache2.0
*
* or in the "license" file accompanying this file. This file is distributed
* on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either
* express or implied. See the License for the specific language governing
* permissions and limitations under the License.
*/
#pragma once
#include <aws/organizations/Organizations_EXPORTS.h>
#include <aws/organizations/model/OrganizationalUnit.h>

namespace Aws
{
template<typename RESULT_TYPE>
class AmazonWebServiceResult;

namespace Utils
{
namespace Json
{
  class JsonValue;
} // namespace Json
} // namespace Utils
namespace Organizations
{
namespace Model
{
  class AWS_ORGANIZATIONS_API CreateOrganizationalUnitResult
  {
  public:
    CreateOrganizationalUnitResult();
    CreateOrganizationalUnitResult(const AmazonWebServiceResult<Aws::Utils::Json::JsonValue>& result);
    CreateOrganizationalUnitResult& operator=(const AmazonWebServiceResult<Aws::Utils::Json::JsonValue>& result);

    /**
     * <p>A structure that contains details about the newly created OU.</p>
     */
    inline const OrganizationalUnit& GetOrganizationalUnit() const{ return m_organizationalUnit; }

    /**
     * <p>A structure that contains details about the newly created OU.</p>
     */
    inline void SetOrganizationalUnit(const OrganizationalUnit& value) { m_organizationalUnit = value; }

    /**
     * <p>A structure that contains details about the newly created OU.</p>
     */
    inline void SetOrganizationalUnit(OrganizationalUnit&& value) { m_organizationalUnit = value; }

    /**
     * <p>A structure that contains details about the newly created OU.</p>
     */
    inline CreateOrganizationalUnitResult& WithOrganizationalUnit(const OrganizationalUnit& value) { SetOrganizationalUnit(value); return *this;}

    /**
     * <p>A structure that contains details about the newly created OU.</p>
     */
    inline CreateOrganizationalUnitResult& WithOrganizationalUnit(OrganizationalUnit&& value) { SetOrganizationalUnit(value); return *this;}

  private:
    OrganizationalUnit m_organizationalUnit;
  };

} // namespace Model
} // namespace Organizations
} // namespace Aws
